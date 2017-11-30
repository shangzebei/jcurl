#ifndef __HelloCpp__DMHttpManager__
#define __HelloCpp__DMHttpManager__

#include <iostream>
#include <map>
#include "HttpClient.h"

enum class ImageCacheType
{
    Default,
    NoMemoryCache,
    NoAllCache
};

class CommonHttpManager
{
    
public:
    
    enum class ResponseStatus
    {
        Succeed,
        Faild,
        TimeOut,
        WebDisabled
    };

    typedef std::function<void(const ResponseStatus&, const CSJson::Value&)> JsonCallback;
    
//    typedef std::function<void(CAImage*, const std::string&)> ImageCallback;
    
    
    static CommonHttpManager* getInstance();
    
    static void destroyInstance();
    
    void send_get(const std::string& url,
                  std::map<std::string, std::string> key_value,
                  const JsonCallback& callback);
    
    void send_post(const std::string& url,
                   std::map<std::string, std::string> key_value,
                   const JsonCallback& callback);
    
    void send_postFile(const std::string& url,
                       std::map<std::string, std::string> key_value,
                       const std::string& file,
                       const JsonCallback& callback);
    
//    void get_image(const std::string& url,
//                   const ImageCallback& callback,
//                   ImageCacheType type = ImageCacheType::Default);
    

    
    void stopActivityIndicatorView();
    
private:
    
    CommonHttpManager();
    
    ~CommonHttpManager();

private:

    std::vector<CAHttpClient*> m_pHttpJsonClients;
    
    std::vector<CAHttpClient*> m_pHttpImageClients;
    

};



#pragma CommonUrlImageView


#endif /* defined(__HelloCpp__DMHttpManager__) */
