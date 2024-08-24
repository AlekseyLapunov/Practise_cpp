#pragma once

#include <iostream>
#include <string>

namespace Data
{
    struct Data
    {
        std::string payload;
    };

    namespace Format
    {
        struct Json : Data
        {
            // pretend that we have some difference here comparing to XML
        };

        struct XML  : Data
        {
            // pretend that we have some difference here comparing to JSON
        };
    }
}

class JsonService
{
public:
    static void doTask(Data::Format::Json obj)
    {
        std::cout << "JsonService doing task on base of JSON object with payload: " << obj.payload << "\n";
    }
};

class ClientInterface
{
public:
    virtual void doTask(Data::Format::XML xmlObj) = 0;
};

class XmlToJsonAdapter : public ClientInterface
{
public:
    void doTask(Data::Format::XML xmlObj) override
    {
        JsonService::doTask(convertFromXml(xmlObj));
    }

private:
    // Pretend that we have real convertion between JSON and XML here
    Data::Format::Json convertFromXml(Data::Format::XML xmlObj)
    {
        Data::Format::Json jsonResult;

        std::string newPayload = xmlObj.payload;

        if (newPayload.find("#XML") != std::string::npos)
            inPlaceReplace(newPayload, "#XML", "#JSON");
        else
            newPayload += "#JSON";
        
        jsonResult.payload = newPayload;

        return jsonResult;
    }

    void inPlaceReplace(std::string& target, const std::string& toBeReplaced, const std::string& replacement)
    {
        size_t pos = 0;
        while ((pos = target.find(toBeReplaced, pos)) != std::string::npos)
        {
            target.replace(pos, toBeReplaced.length(), replacement);
            pos += replacement.length();
        }
    }
};
