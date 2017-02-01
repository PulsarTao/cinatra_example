//
// Created by 邢俊杰 on 2017/2/1.
//

#include <iostream>
#include <string>
#include <cinatra_http/http_server.h>


// 可访问
//  http://127.0.0.1:8086/
//  https://127.0.0.1:8087/
//  等进行测试
int main()
{
    cinatra::http_server s(4);
    s.request_handler([](cinatra::request const& req, cinatra::response& res)
                      {
                          res.response_text("Hello world!");
                      });

    s.listen("0.0.0.0", "8086");
    s.listen("0.0.0.0", "8087", cinatra::http_server::tlsv12,
             R"key(-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEA2WP8jtcLmF8YzsJqVJFj3Zs3PUeXP6sh4NhTq2zdO5UrJuz1
+BGZAclJ3UpY/o6xTe5FfAhGQL+qu5QOMGiRpd6laEMKxbXrPq2ObAXhXPSaburm
TVgRY+Yt+AZooaARbrmbylz8GK2B00c16WFMRz5hLgrbOaZKz/2Y1lvQJNUVWkTq
BYcw0q9xLwb6qf2W5O9Zr4ol8Tb79chn6kt5CI+0IdYgcV8qxkVcpeDn9z3WLYCN
l7SEv0VFVmhqOffDZoNFFH355Pfi+DZvtIjbbMquGW1YBfoXKa3Kocm0kNu4Yj8N
yr5tWMdwQtTQzGud25UF5418ucwr3boSimDvwQIDAQABAoIBAQCdNlz4Y/ZjvCox
pJHHFNn28oAxVevAxJ8cfvWLXJBlvYvWe7mqK/fOPeaoHVNczI7XAADKISXFP5dW
Tk0wnv7tyKUwUIOi1dwJmPQNlPcVBWQF4OSqfI0fBOCrpN7YO+0/eQV8hGBf7GKe
C7qmS5IhV7Bp3roJ6APkhM6Z/w35A7ZcdICmKS3wYtzsZ9fiB4Rj1sZ0KBKUik+a
+TDcJO/4JQNDUZgBc5odFEjL3AE+ltVmWOZ7UoOPLfy7Tuds8Wkwubcu/52RTTyE
Ul94Nssc0HQoCkcLEAUDxvMZowyCHHUgj142DrfHoJwNCJbslpAxSJqb8kXYlMvo
D9l4ipMNAoGBAP5xQhz0qQaSrzheDOWZBEdp2y6pPrLiwUiuhC61RlBr9CbyuUoj
0Td4R3hsYlLuOgZp02GLY9U7mVwmy0ywJqTAABrsiCkkaFh5WFSNlpPurpxVWAFv
dUf7eGqjcBlPZuPJrZE8S0nuBMJ+hDgMsb/37zTpGmUdP1Y4JVbxKhl/AoGBANq4
qeNHQAyF4UlPj24InwHjNjTJCjOoIs82hI+DtYOhajwBIDNQptDCSZZr/kxL6/mm
vq8y2VCj4fJ1aEkcxMQW8BnS4jXtMDDZx4Yc9/RS4mz4t8C9d9GH/bFFVwo+Ofx1
U6nHugsoTKNVT/RCO3xUagSV1IpOUWfTdj/vuRa/AoGAZGFMQt4m3Mf7xpIcJmxS
qtXRObxdVvdsZ38p+L9dSRb90GvLu7sbq/WQxKqFs8/2JleTpBT4wsPrgdZwOAX6
iN6SbAzKvuh1HgppVZoyQJRWYKiuuoo9S7Oi0vc9n06a+dyz0+tkjHsRd6WwBejE
K0bmIQqhdiiutxYZbQ5hnIMCgYEAykLssAXKoAoKfN37GFkWmgtArG2hZoW8svyK
d6Dn8XMKp7Suz2Vs7i5NGLKDdpDbBoIBYkjWl/EFWE7kgn/9IgzIOkk+8XmHEBXE
oiwVzDX9t6IFY1KTBAwLOaySwiErRGBHXwEY9Ypt3Lle99Vr5xy08cqQwtmMBEST
3KpV8kcCgYA063aCxy0o26vZprQiPp0ycdZauU04mSpZPKjuK5Xy4zGllvudMIs1
5g8rpbOOf+GnHZDEUr1qeTefULOemtQdmtLzKgr/U0WdV8TXcih4ZKQzWAKSDVib
mKcoPQ39fuQumYbXQ3jzOvmltnqGBwOPmrQIz1dPpm1hAC/rvNqEtQ==
-----END RSA PRIVATE KEY-----
)key",
             R"crt(-----BEGIN CERTIFICATE-----
MIIDBjCCAe4CCQD6XjOU5UDvMzANBgkqhkiG9w0BAQUFADBFMQswCQYDVQQGEwJB
VTETMBEGA1UECBMKU29tZS1TdGF0ZTEhMB8GA1UEChMYSW50ZXJuZXQgV2lkZ2l0
cyBQdHkgTHRkMB4XDTE3MDIwMTExMDYwN1oXDTE4MDIwMTExMDYwN1owRTELMAkG
A1UEBhMCQVUxEzARBgNVBAgTClNvbWUtU3RhdGUxITAfBgNVBAoTGEludGVybmV0
IFdpZGdpdHMgUHR5IEx0ZDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB
ANlj/I7XC5hfGM7CalSRY92bNz1Hlz+rIeDYU6ts3TuVKybs9fgRmQHJSd1KWP6O
sU3uRXwIRkC/qruUDjBokaXepWhDCsW16z6tjmwF4Vz0mm7q5k1YEWPmLfgGaKGg
EW65m8pc/BitgdNHNelhTEc+YS4K2zmmSs/9mNZb0CTVFVpE6gWHMNKvcS8G+qn9
luTvWa+KJfE2+/XIZ+pLeQiPtCHWIHFfKsZFXKXg5/c91i2AjZe0hL9FRVZoajn3
w2aDRRR9+eT34vg2b7SI22zKrhltWAX6FymtyqHJtJDbuGI/Dcq+bVjHcELU0Mxr
nduVBeeNfLnMK926Eopg78ECAwEAATANBgkqhkiG9w0BAQUFAAOCAQEAM1HVcZVH
1CtMo1prqgegVkpANm7bD17CJCpTMrkRCZbO+e4Jm/Pv/G+2U1C+PzRYE1YoClzo
nX35F9lgDsC3OmCzlPjRicacx5uHIZoAJI/Ms949BRRbKFUVEnyHB911o9xmM6fj
ZN29hWGCEfkTKLMsng9qD6U6tAHMGhmgIaPllYVm+rAXVmbnolR98MD+jTfjy/LW
q+h1y3sM337WzTKPe+MZCHHN0UarPYQAUF3Ya5ZMPDs5z6fEVRlnpBtATieXY71v
km0Y6QEcWxdXo2KOZXRHffNUDP3Ia0zbUCJ7KNeE0TFqc9iq75xSLPPoudp3E5d4
ln4jjQvAh/dw8g==
-----END CERTIFICATE-----
)crt", false);
    s.run();

    return 0;
}