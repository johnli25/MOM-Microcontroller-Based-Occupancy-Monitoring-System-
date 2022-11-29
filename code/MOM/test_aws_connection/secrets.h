#ifndef SECRETS_H
#define SECRETS_H

// To import the PROGMEM macro (https://www.arduino.cc/reference/en/language/variables/utilities/progmem/)
#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32-Feather"

const char WIFI_SSID[] = "IllinoisNet_Guest";
const char WIFI_PASSWORD[] = "";
const char AWS_IOT_ENDPOINT[] = "a3ulqjae98hapx-ats.iot.us-east-1.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAO/iBAZumGXizFqJYKyfOI39avhuMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjEwMzAxNTE1
NDFaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC7qVrE9P7MpRw07H1E
OyPznfRPsRbNetpPWWzn6y/WYvdXmymFXzmvtXW15SUedXTnaOT2X8dGcB6TuVq+
bsMi1YfC9sDowhSi1LwvnprWUZBPJXSpmEUltAFiArrwZ+y0EwDGFWERfPAOvdte
QSSdQR20wyyH4JrRoSzez4DtIud+S9J6/qWV8Fz7MBOKMAByZiVZQixsJG9D7H3B
dcv8NLvYdB96Oo7qKJi8rtDmglSSz5o4t3qVWQaugW3hZp5mbi/t+VVHEHnmvRCn
OQ5E8t0A3WXxBg3fAcV5Ytx9warpVRzb2TmaomCZYEdeF3HzldBV+q7FgLthoW/h
2yB7AgMBAAGjYDBeMB8GA1UdIwQYMBaAFJk7JWcaKcIepitf70ieZ4jYVEmeMB0G
A1UdDgQWBBQDN2rhbehYSsLx6X5sL5NMsag1lzAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAePYR62SQost/iqsHrYh6ngs6
qql7FjI9rbTOzTUbk3qQkQpr/Zr4c7y2tqcooVLeb/lrhotX1Um1b4paoIi3yiPP
y1Kee9a3ijVewMiUCwQ49rA9DMtayMPUzmUvJ7hoWxom5KGHRb/3Bo7O/t4Tlrhx
uKOkW2Eh5YbRdJodgDuxdx4NIUKA3B0rmgvIlygdi3RH5B9Qj5zM7BlC5eXnT03p
92lOUgbtpqid2oxHwFnyQK3OWzohrRKGTtHneWopZGazBXa2X0hgu9p4rUwk/qmi
p+xXFHBFCROVi6gQzhWf2IDI3mJGNETbTYBRrgFvw0V+nbEIwelU1xZO3h5AxA==
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAu6laxPT+zKUcNOx9RDsj8530T7EWzXraT1ls5+sv1mL3V5sp
hV85r7V1teUlHnV052jk9l/HRnAek7lavm7DItWHwvbA6MIUotS8L56a1lGQTyV0
qZhFJbQBYgK68GfstBMAxhVhEXzwDr3bXkEknUEdtMMsh+Ca0aEs3s+A7SLnfkvS
ev6llfBc+zATijAAcmYlWUIsbCRvQ+x9wXXL/DS72HQfejqO6iiYvK7Q5oJUks+a
OLd6lVkGroFt4WaeZm4v7flVRxB55r0QpzkORPLdAN1l8QYN3wHFeWLcfcGq6VUc
29k5mqJgmWBHXhdx85XQVfquxYC7YaFv4dsgewIDAQABAoIBACbG2dC05ymWPHvb
Gg9NQSKH0wHcj9+psQ6QZeaOPHZKQN3DXBMJGDxsfIQ3czIWBzACBr26EM1HQao4
tL2A2aWLBeCNaFMwN19mIfSdC1WZyP3xuWeJ5U/jIB4GfmZKsyiKfLBxnnskm94P
8RJK16v+1oqRgdQZ3yPN8B2iNvvIzfiB7TFTtO5YN9nGjeUahUC+MHoRewrNCH24
XfuEPiy/dZHJR1Lx65sldtONXnhBSFXCViVGpqQ3atFhppMZ7zqNgZTg8MBs2PsK
wOnL10m5fZBoUFTYbamGrSEpyPVreYOoqfgxQSMh8WWVGB7a5AZy9tG0JZL9mVyi
gAEV9mECgYEA4irFrP19h0PEbB5I4dKM98jvBNoNviMAFJ9s6JjL7St46fyQLve2
Azwrg416wLYY9pow65OHML3TI5rgPb0hVMwXQDFAhpcNIuQbZ5s8PxBWTKrVKh/P
sc4hG9ITjZjICuFSt7AcAj3q9kytaSHkAxxsL89gVoAjQItq9q0TPokCgYEA1GpT
CQji9iE52cMcNSoTIPLmTE/U8aBdRNnKtp8TLB1XF6rWRQuC8n+AgUJUp1DkwyBh
qVJV6MWGb0E3tCdv2nmfHCeYmghXP2uESL0a7A+72D/XS7ZuAPyRcSIYB7dobHB4
ZuTTTxk1To6qNzL04aOSySg3Eui2b6QekQiCBeMCgYAE681VUEa09MKHX7lSQJSU
p6ibwGrgIj7UNAvYm8qEJJgC713rx7QMKfkAacmr+8pbQ0uhNJqScu7vLWWHsl/R
SoeO/ANdalf81F3MSVJsRNy72lO9EOgiBEwwIMgQIqznn7N/D7PsUJCWP2DeksA1
WR75g1ejSjJ6Kw5uw6FRkQKBgQDSmNfajUT4YdjJXfgJfb2ZXTmXT08AgM34BTZF
+VE4254NiQMHUXJympb9kJX9jOZBz0kEZu1l6vBuPWrM4oyzPwHRGDDkBoD6D88H
jvWyNac3r5P1LNnDgKVyVSsd+2k8mgXFfflC4utHB4sbTxoa2+IcLhLsXG0EIuNr
R9QhoQKBgQDSywDCQ334IqlTrPjzNijqKxgAr7ev1OaqwkF1GEfyR365QMuxuBrl
J2ZFrBdJzZ7RlrH90oLvLjS1KVb4hJrUWGRt+y7kJAzRaXicOEIOSWgSEiKcSoSr
8XV7nVO5Zv+Ggepv2bbkoGL7dJRmguu0GWkSbb85b8UIMdK9B5oucg==
-----END RSA PRIVATE KEY-----
)KEY";

#endif /* SECRETS_H */