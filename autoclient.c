/*
	autoclient.c

	Example calculator service client in C

	Compilation in C :
	$ soapcpp2 -c auto.h
	$ cc -o autoclient autoclient.c stdsoap2.c soapC.c soapClient.c
	where stdsoap2.c is in the 'gsoap' directory, or use libgsoap:
	$ cc -o autoclient autoclient.c soapC.c soapClient.c -lgsoap

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2001-2008, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL or Genivia's license for commercial use.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapH.h"
#include "setAuto.nsmap"

const char server[] = "http://192.168.1.120:8080";
/* = "http://localhost:8080"; to test against samples/webserver */

int main(int argc, char **argv)
{ struct soap soap;
  double a, b, result;
  if (argc < 4)
  { fprintf(stderr, "Usage: [setAuto] num[Sentido] num[Direccion]\n");
    exit(0);
  }
  soap_init1(&soap, SOAP_XML_INDENT);
  a = strtod(argv[2], NULL);
  b = strtod(argv[3], NULL);
  switch (*argv[1])
  { case 's':
      soap_call_ns__setAuto(&soap, server, "", a, b, &result);
      break;
    default:
      fprintf(stderr, "Unknown command\n");
      exit(0);
  }
  if (soap.error)
  { soap_print_fault(&soap, stderr);
    exit(1);
  }
  else
    printf("result = %g\n", result);
  soap_destroy(&soap);
  soap_end(&soap);
  soap_done(&soap);
  return 0;
}
