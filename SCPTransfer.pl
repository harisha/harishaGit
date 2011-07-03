#!/usr/bin/perl

use strict;
use warnings;

use Net::SCP 'scp','iscp';

print <<EOF;

Script Usage:
{
For Getting Files 

Source: harisha@<ipAddress>:/home/harisha/Music/
Destination: /home/harisha/temp

For Sending Files

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
scp($source,$destination) or die "scp fail"; 


