#include "schema.h" //rapidjson
#include "document.h" //rapidjson
#include "writer.h" //rapidjson
#include "reader.h" //rapidjson
#include "stringbuffer.h" //rapidjson
#include "error/error.h" // rapidjson::ParseResult
#include "error/en.h" // rapidjson::ParseResult
#include <iostream>

int main(){
    rapidjson::Document sd;
    std::string schemaJson="{\"$schema\":\"http://json-schema.org/draft-04/schema#\",\"id\":\"http://jsonschema.net\",\"type\":\"object\",\"properties\":{\"address\":{\"id\":\"http://jsonschema.net/address\",\"type\":\"object\",\"properties\":{\"streetAddress\":{\"id\":\"http://jsonschema.net/address/streetAddress\",\"type\":\"string\"},\"city\":{\"id\":\"http://jsonschema.net/address/city\",\"type\":\"string\"}},\"required\":[\"streetAddress\",\"city\"]},\"phoneNumber\":{\"id\":\"http://jsonschema.net/phoneNumber\",\"type\":\"array\",\"items\":{\"id\":\"http://jsonschema.net/phoneNumber/0\",\"type\":\"object\",\"properties\":{\"location\":{\"id\":\"http://jsonschema.net/phoneNumber/0/location\",\"type\":\"string\"},\"code\":{\"id\":\"http://jsonschema.net/phoneNumber/0/code\",\"type\":\"integer\"}}}}},\"required\":[\"address\",\"phoneNumber\"]}";
    //see http://jsonschema.net/ for automatic schema generator
    if (sd.Parse(schemaJson.c_str()).HasParseError()) {
        std::cout<<"line 17"<<std::endl;      
    }
    rapidjson::SchemaDocument schema(sd); // Compile a Document to SchemaDocument
    // sd is no longer needed here.
    rapidjson::Document d;
    std::string inputJson="{  \"address\": { \"streetAddress\": \"21 2nd Street\", \"city\": \"New York\" },\"phoneNumber\": [   {  \"location\": \"home\", \"code\": 44  }]}";
    if (d.Parse(inputJson.c_str()).HasParseError()) {
        std::cout<<"line 26"<<std::endl; 
    }
    rapidjson::SchemaValidator validator(schema);
    if (!d.Accept(validator)) {
        // Input JSON is invalid according to the schema
        // Output diagnostic information
        rapidjson::StringBuffer sb;
        validator.GetInvalidSchemaPointer().StringifyUriFragment(sb);
        std::cout<<sb.GetString()<<std::endl;
        std::cout<<validator.GetInvalidSchemaKeyword()<<std::endl;
        sb.Clear();
        validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);
        std::cout<< sb.GetString()<<std::endl;
    }    
}