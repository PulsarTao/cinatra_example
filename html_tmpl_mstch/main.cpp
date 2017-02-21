//
// Created by 邢俊杰 on 2017/2/21.
//

#include <cinatra/cinatra.h>
#include <mstch/mstch.hpp>

cinatra::response render(std::string const& tpl, mstch::map const& model)
{
    std::ifstream t("./template/" + tpl + ".tpl", std::ios::binary | std::ios::in);
    if (!t.is_open())
    {
        return cinatra::response::stock_reply(cinatra::response::not_found);
    }
    t.seekg(0, std::ios::end);
    auto size = t.tellg();
    std::string buffer(size,'\0');
    t.seekg(0);
    t.read(&buffer[0], size);

    cinatra::response res;
    res.add_header("Content-Type", "text/html; charset=utf-8");
    res.response_text(mstch::render(buffer, model));

    return res;
}

int main()
{
    cinatra::cinatra<> s;
    s.route("/", [](cinatra::response& res)
    {
        mstch::map model{
                {"names", mstch::array{
                        mstch::map{{"name", std::string{"Chris"}}},
                        mstch::map{{"name", std::string{"Mark"}}},
                        mstch::map{{"name", std::string{"Scott"}}},
                }}
        };

        res = render("Hello", model);
    });
    s.route("/str", [](cinatra::response& res)
    {
        mstch::map model{
                {"names", mstch::array{
                        mstch::map{{"name", std::string{"Chris"}}},
                        mstch::map{{"name", std::string{"Mark"}}},
                        mstch::map{{"name", std::string{"Scott"}}},
                }}
        };

        res.response_text(mstch::render("{{#names}}Hi {{name}}!\n{{/names}}", model));
    });

    s.listen("0.0.0.0", "8086");
    s.run();
    return 0;
}