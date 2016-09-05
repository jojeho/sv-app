#pragma once

struct rtime_client
{
    std::unique_ptr<jeho::network::dump::client> client_;
	
    rtime_client()
    {
       auto con = std::make_shared<jeho::network::connection>(base_host(), base_port());
       client_ = std::make_unique<jeho::network::dump::client>(con);
    }

    template<typename T>
    void send(T const&t)
    {

    }
};
