/***************************************************************
 My own Pushover Library, based on this one from GitHub
 https://github.com/ArduinoHannover/Pushover
 
 While the referenced lib works just fine, I needed much better errorhandling, not just false or true and debugging.
 The return value is therefore int instead of boolean.
 There is also an additional Setter to set a debug flag.
 
 Returns:
 0:         ok message sent, return was HTTP/1.1 200
 2:         return was HTTP/1.1 400, bad request (token/userkey, Message with errors)
 3:         no connection to server api.pushover.net
 4:         timeout
  
 ******************************************************************* 
 */
#include <WiFiClientSecure.h>

class myPushover {
	private:
		String _token;
		String _user;
		String _message;
		String _device;
		String _title;
		String _url;
		String _url_title;
		int8_t _priority = 0;
		uint16_t _retry;
		uint16_t _expire;
		uint32_t _timestamp = 0;
		boolean _html;
		uint16_t _timeout = 5000;
		String _sound;
		int8_t returncode;
		boolean _debug;
	public:
		myPushover(String,String);
		void setMessage(String);
		void setDevice(String);
		void setTitle(String);
		void setUrl(String);
		void setUrlTitle(String);
		void setPriority(int8_t);
		void setRetry(uint16_t);
		void setExpire(uint16_t);
		void setTimestamp(uint32_t);
		void setSound(String);
		void setHTML(boolean);
		void setTimeout(uint16_t);
		void setDebug(boolean);
		int send(void);
};
