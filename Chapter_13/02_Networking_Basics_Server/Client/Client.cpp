#include "Client.h"

Client::Client() : m_listenThread(&Client::Listen, this) {}
Client::~Client() { m_socket.unbind(); } // unbind from the port

bool Client::Connect()
{
	if (m_connected) { return false; }
	m_socket.bind(sf::Socket::AnyPort);
	std::cout << "Bound client to port: " << m_socket.getLocalPort() << std::endl;
	sf::Packet p;
	StampPacket(PacketType::Connect, p);
	p << m_playerName;
	if (m_socket.send(p, m_serverIp, m_serverPort) != sf::Socket::Done) { m_socket.unbind(); return false; }
	m_socket.setBlocking(false);
	p.clear();
	sf::IpAddress recvIP;
	PortNumber recvPORT;
	sf::Clock timer;
	timer.restart();

	std::cout << "Attempting to connect to: " << m_serverIp << ":" << m_serverPort << std::endl;
	while (timer.getElapsedTime().asMilliseconds() < CONNECT_TIMEOUT)
	{
		sf::Socket::Status status = m_socket.receive(p, recvIP, recvPORT);
		if (status != sf::Socket::Done) { continue; }
		if (recvIP != m_serverIp) { continue; }
		PacketID id;
		if (!(p >> id)) { break; }
		if ((PacketType)id != PacketType::Connect) { continue; }
		m_packetHandler(id, p, this);
		m_connected = true;
		m_socket.setBlocking(true);
		m_lastHeartbeat = m_serverTime;
		m_listenThread.launch();
		return true;
	}
	std::cout << "Connection attempt failed! Server info: " << m_serverIp << ":" << m_serverPort << std::endl;
	m_socket.unbind();
	m_socket.setBlocking(true);
	return false;
}

bool Client::Disconnect()
{
	if (!m_connected) { return false; }
	sf::Packet p;
	StampPacket(PacketType::Disconnect, p);
	sf::Socket::Status status = m_socket.send(p, m_serverIp, m_serverPort);
	m_connected = false;
	/*	When a socket is in blocking mode, its receive method waits until some
		data arrives before continuing. Having something like that happen in a
		separate thread would leave it running, and therefore stop our program
		from quitting. One way to prevent that is by unbinding a socket that is
		being used. It makes the receive method return an error, which we have
		handled in the Listen method of our client class.*/
	m_socket.unbind(); // Unbind to close the listening thread.
	if (status != sf::Socket::Done) { return false; }
	return true;
}

void Client::Listen()
{
	sf::Packet packet;
	sf::IpAddress recvIP;
	PortNumber recvPORT;
	std::cout << "Beginning to listen..." << std::endl;
	while (m_connected)
	{
		packet.clear();
		/* !!!Because the socket is in blocking mode, the listening thread
		   will halt at the m_socket.receive(...) line until some data comes in.*/
		sf::Socket::Status status = m_socket.receive(packet, recvIP, recvPORT);
		if (status != sf::Socket::Done)
		{
			if (m_connected)
			{
				std::cout << "Failed receiving a packet from " << recvIP << ":" << recvPORT 
					<< ". Status: " << status << std::endl;
				continue;
			}
			else
			{
				std::cout << "Socket unbound." << std::endl;
				break;
			}
		}
		if (recvIP != m_serverIp)
		{
			// // Ignore packets not sent from the server.
			std::cout << "Invalid packet received: invalid origin." << std::endl;
			continue;
		}
		PacketID p_id;
		if (!(packet >> p_id))
		{
			// Non-conventional packet.
			std::cout << "Invalid packet received: unable to extract id." << std::endl;
			continue;
		}
		PacketType id = (PacketType)p_id;
		if (id < PacketType::Disconnect || id >= PacketType::OutOfBounds)
		{
			// Invalid packet type.
			std::cout << "Invalid packet received: id is out of bounds." << std::endl;
			continue;
		}

		if (id == PacketType::Heartbeat)
		{
			sf::Packet p;
			StampPacket(PacketType::Heartbeat, p);
			if (m_socket.send(p, m_serverIp, m_serverPort) != sf::Socket::Done)
			{
				std::cout << "Failed sending a heartbeat!" << std::endl;
			}
			sf::Int32 timestamp;
			packet >> timestamp;
			SetTime(sf::milliseconds(timestamp));
			m_lastHeartbeat = m_serverTime;
		}
		else if (m_packetHandler)
		{
			m_packetHandler((PacketID)id, packet, this); // Handle the packet
		}
	}
	std::cout << "...Listening stopped." << std::endl;
}

bool Client::Send(sf::Packet& l_packet)
{
	if (!m_connected) { return false; }
	if (m_socket.send(l_packet, m_serverIp, m_serverPort) != sf::Socket::Done) { return false; }
	return true;
}

const sf::Time& Client::GetTime() const
{
	return m_serverTime;
}

const sf::Time& Client::GetLastHeartbeat() const
{
	return m_lastHeartbeat;
}

void Client::SetTime(const sf::Time& l_time)
{
	m_serverTime = l_time;
}

void Client::SetServerInformation(const sf::IpAddress& l_ip, const PortNumber& l_port)
{
	m_serverIp = l_ip;
	m_serverPort = l_port;
}

void Client::SetUp(void(*l_handler)(const PacketID&, sf::Packet&, Client*))
{
	m_packetHandler = std::bind(l_handler, 
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void Client::UnregisterPacketHandler()
{
	m_packetHandler = nullptr;
}

void Client::Update(const sf::Time& l_time)
{
	if (!m_connected) { return; }
	m_serverTime += l_time;
	if (m_serverTime.asMilliseconds() < 0)
	{
		m_serverTime -= sf::milliseconds(sf::Int32(Network::HighestTimestamp));
		m_lastHeartbeat = m_serverTime;
		return;
	}
	if (m_serverTime.asMilliseconds() - m_lastHeartbeat.asMilliseconds() >= sf::Int32(Network::ClientTimeout))
	{
		// Timeout
		std::cout << "Server connection timed out!" << std::endl;
		Disconnect();
	}
}

bool Client::IsConnected() const { return m_connected; }
void Client::SetPlayerName(const std::string& l_name) { m_playerName = l_name; }

sf::Mutex& Client::GetMutex() { return m_mutex; }