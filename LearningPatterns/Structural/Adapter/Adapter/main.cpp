#include <iostream>
#include <memory>

#include "adapter_demo.hpp"

int main()
{
    std::unique_ptr<ClientInterface> client = std::make_unique<XmlToJsonAdapter>();

    Data::Format::XML xmlObj;
    xmlObj.payload = "Data! #XML";

    client.get()->doTask(xmlObj);

    return 0;
}