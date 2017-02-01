//
// Created by 邢俊杰 on 2017/2/1.
//

#include <iostream>
#include <string>
#include <cinatra_http/http_server.h>


// 可访问
//  http://127.0.0.1:8086/
//  http://127.0.0.1:8086/test
//  http://127.0.0.1:8086/test?a=b&c=d&e=f
//  等进行测试
int main()
{
    cinatra::http_server s(4);
    s.request_handler([](cinatra::request const& req, cinatra::response& res)
    {
        static const std::string beg = R"---(
<!DOCTYPE html>
<html>
<head>
	<title>cinatra http server</title>
</head>
<body>
)---";
        static const std::string end = R"---(
</body>
</html>
)---";

        std::string res_str;

        res_str += beg;

        res_str += "<h1>Request path</h1>";
        res_str += "<p>";
        res_str += req.path().to_string();
        res_str += "</p></br>";

        res_str += "<h1>Request query</h1></br>";
        for (auto const& kv : req.query())
        {
            res_str += "<p>";
            res_str += kv.first;
            res_str += ": ";
            res_str += kv.second;
            res_str += "</p></br>";
        }


        res_str += "<h1>Request headers</h1></br>";
        for (auto const& header : req.get_headers())
        {
            res_str += "<p>";
            res_str += header.name.to_string();
            res_str += ": ";
            res_str += header.value.to_string();
            res_str += "</p></br>";
        }

        res_str += end;

        res.response_text(res_str);
    });

    s.listen("0.0.0.0", "8086");
    s.run();

    return 0;
}