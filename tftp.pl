#!/usr/bin/perl

use warnings;
use strict;
use TFTP;

my $numOfArgs=$#ARGV+1;

if($numOfArgs != 3)
{
	print "\n Usage: tftp.pl <IpAddress> <cmd-get/put> <fileName>";
	exit;
}

my $tftp;

$tftp=new TFTP($ARGV[0]) or die "object creation failed $!";
if($ARGV[1] eq "get")
{
	print "File --> $ARGV[2]\n";
	$tftp->get($ARGV[2]) or die "get fail $!";
}
elsif($ARGV[1] eq "put")
{
	print "File --> $ARGV[2]\n";
	$tftp->octet;
	$tftp->put($ARGV[2]) or die "put $!";
}
else
{
	print "Please Enter Valid TFTP Command \n";
}

$tftp->quit or die "TFTP quit failed $!";




