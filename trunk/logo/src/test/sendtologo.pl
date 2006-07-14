#! /usr/bin/perl -c
############################################################
# A simple test application that opens a socket to a given
# host/port, sends some data, then closes the socket.
#
# Usage: sendtologo.pl <hostname> <port>
#
# This is part of network.lgo
#
############################################################

use Socket;
use strict;

my $proto = getprotobyname('tcp');
socket(SOCKET, PF_INET, SOCK_STREAM, $proto);
my $port = $ARGV[1];
my $sin = sockaddr_in($port, inet_aton($ARGV[0]));

connect(SOCKET, $sin) or die $!;

print SOCKET "hello" or die $!;

close (SOCKET) or die $!;
