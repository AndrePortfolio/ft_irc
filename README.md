# ft_irc

## Introduction
**ft_irc** is an implementation of an Internet Relay Chat (IRC) server in C++. It demonstrates a solid understanding of networking concepts, the TCP/IP protocol, and non-blocking I/O operations. The project complies with the C++98 standard and supports multiple clients interacting simultaneously in real-time.

![IRC Server Diagram](https://github.com/AndrePortfolio/irc/blob/main/irc.png)

## Features
- Handles multiple clients concurrently using non-blocking file descriptors and a single `poll()` loop (or equivalent).
- Implements basic IRC functionality, including:
  - Authentication with a password.
  - Setting nicknames and usernames.
  - Joining and managing channels.
  - Sending and receiving private and channel messages.
- Supports channel operators with the following commands:
  - **KICK**: Eject a client from a channel.
  - **INVITE**: Invite a client to a channel.
  - **TOPIC**: View or change the channel topic.
  - **MODE**: Manage channel modes:
    - `i`: Invite-only channel.
    - `t`: Restrict `TOPIC` command to operators.
    - `k`: Set/remove a channel key (password).
    - `o`: Assign/remove operator privileges.
    - `l`: Set/remove a user limit for the channel.

## Usage
Run the IRC server executable with the following parameters:

```bash
git@github.com:AndrePortfolio/ft_irc.git
cd ft_irc
make
./ircserv 4242 IRC
