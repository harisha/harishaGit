#!/usr/bin/perl

use warnings;
use strict;

use TFTP;

my $tftp;
$tftp=new TFTP("192.168.1.2") or die "TFTP object failed $@";
$tftp->get("Hello.txt")  or die "TFTP get failed $@";
$tftp->quit or die "TFTP quit failed $@";

