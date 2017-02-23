//
// Created by 邢俊杰 on 2017/2/22.
//

#include <cinatra/cinatra.h>
#include <mstch/mstch.hpp>
#include <cinatra/middleware/session.hpp>
#include <cinatra_http/utils.h>

#include <string>
#include <unordered_map>

struct check_login_aspect
{
    void before(cinatra::request const& req, cinatra::response& res, cinatra::context_container& ctx)
    {
        // 访问的是登录页面，不用检查是否已登录
        if (req.path() == "/login")
        {
            return;
        }
        auto s = ctx.get_req_ctx<cinatra::session>();
        // session中没有用户名
        if (!s.has("uid"))
        {
            res = cinatra::response::stock_reply(cinatra::response::moved_permanently);
            res.add_header("location", "/login");
            return;
        }
    }

    void after(cinatra::request const& req, cinatra::response& res, cinatra::context_container& ctx) {}

    class context_t {};
};

int main()
{
    cinatra::cinatra<cinatra::cookies, cinatra::session, check_login_aspect> s;

    s.get_middleware<cinatra::session>().set_timeout(50);

    s.route("/", [](cinatra::response& res, cinatra::context_container& ctx)
    {
        auto s = ctx.get_req_ctx<cinatra::session>();

        res.response_text("Hello " + s.get<std::string>("uid"));
    });

    s.route("/login",[](cinatra::request const& req, cinatra::response& res, cinatra::context_container& ctx)
    {
        if (req.method() == "GET")
        {
            std::string html =
R"__(<!DOCTYPE html>
<html>
<head>
	<title>Login</title>
</head>
<body>
<form method="POST">
	<table align="center">
		<tr>
			<td>User name:</td>
			<td>
				<input type="text" name="UID">
			</td>
		</tr>
		<tr>
			<td>Password:</td>
			<td>
				<input type="password" name="PWD">
			</td>
		</tr>
		<tr>
			<td colspan="2" align="center">
				<input type="submit">
			</td>
		</tr>
	</table>
</form>
</body>
</html>)__";
            res.add_header("Content-Type", "text/html; charset=utf-8");
            res.response_text(html);
        }
        else if (req.method() == "POST")
        {
            // TODO: 将解析表单POST数据改为req.form()
            auto body = req.body();
            std::unordered_map<std::string, std::string> kv;
            cinatra::kv_parser(body.begin(), body.end(), kv, '=', '&', true, false);

            auto uid_it = kv.find("UID");
            auto pwd_it = kv.find("PWD");
            if (uid_it == kv.cend() || pwd_it == kv.cend() || uid_it->second.empty() || pwd_it->second != "123456")
            {
                res = cinatra::response::stock_reply(cinatra::response::unauthorized);
                return;
            }

            auto s = ctx.get_req_ctx<cinatra::session>();
            s.add("uid", uid_it->second);

            // TODO: 添加 res.redirect()功能
            res = cinatra::response::stock_reply(cinatra::response::moved_permanently);
            res.add_header("location", "/");
        }
        else
        {
            res = cinatra::response::stock_reply(cinatra::response::not_found);
        }
    });
    s.listen("0.0.0.0", "8080");
    s.run();

    return 0;
}