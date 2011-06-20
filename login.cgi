#!/usr/bin/perl

use strict;
use warnings;

use CGI;

my $cgi=new CGI; #read in parameters
if ($ENV{"REQUEST_METHOD"} eq "GET") 
{
	
	print $cgi->header(); #print a header
        print $cgi->start_html("Welcome To My Page");           #generate HTML document start
	print("Access Denied");
        print $cgi->end_html();        
}
else
{
	
	print $cgi->header(); #print a header
	print $cgi->start_html("Welcome To My Page");      	#generate HTML document start
        
        #check username and password matches "harisha"&"harisha"
	if(($cgi->param('Username')=~m/harisha/) and ($cgi->param('Password')=~m/123456/))
	{
		 print "<h1>Welcome To My Main Page</h1";	
	}
	else
	{
		print "<h1>Invalid Credentials </h1>";
	}
	print $cgi->end_html();                 	#finish HTML document
	#print("Using POST Method");
}

