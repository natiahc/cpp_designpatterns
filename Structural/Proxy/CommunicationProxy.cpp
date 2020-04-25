#include "stdafx.h"
#include <iostream>
#include <ostream>
#include <memory>
#include <string>

#include <cpprest\http_client.h>

struct Pingable
{
	virtual ~Pingable() = default;
	virtual std::wstring ping(const std::wstring& message) = 0;
};

struct Pong : Pingable
{
	std::wstring ping(const std::wstring& message) override
	{
		return message + L" pong";
	}
};

struct RemotePong : Pingable
{
	std::wstring ping(const std::wstring& message) override
	{
		web::http::client::http_client client(U("http://localhost:9150/"));
		web::http::uri_builder builder(U("/api/pingpong"));
		builder.append(message);
		pplx::task<std::wstring> task = client.request(web::http::methods::GET, builder.to_string())
			.then([=](web::http::http_response r) 
		{
			return r.extract_string();
		});

		task.wait();

		return task.get();
	}
};

void tryit(Pingable& p)
{
	std::wcout << p.ping(L"ping") << "\t";
}

int main()
{
	//Pong pp;
	RemotePong rp;
	for (size_t i = 0; i<10; i++)
	{
		tryit(rp);
	}

	return 0;
}