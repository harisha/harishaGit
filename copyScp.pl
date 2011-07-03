#!/usr/bin/perl

use strict;
use warnings;

use Net::SCP 'scp','iscp';

print <<EOF;

Script Usage:
{
For Getting Files like Music ---> temp

Source: harisha@192.168.1.2:/home/harisha/Music/
Destination: /home/harisha/temp

For Sending Files
temp ---> Desktop

Source: /home/harisha/temp
Destination: harisha@<ipAddress>:/home/harisha/Desktop 
}
EOF

print "Enter the Source file to be copied \n";
my $source=<STDIN>;
chomp($source);
print "Entered file is ---> $source \n";

print "Enter the Destination directory where file to be placed \n";
my $destination=<STDIN>;
chomp($destination);
iscp($source,$destination) or die "scp fail"; 


