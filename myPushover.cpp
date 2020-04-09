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
#include "myPushover.h"

myPushover::myPushover(String token, String user) {
	_token = token;
	_user = user;
	_debug = false;
}
void myPushover::setMessage(String message) {
	_message = message;
}
void myPushover::setDevice(String device) {
	_device = device;
}
void myPushover::setTitle(String title) {
	_title = title;
}
void myPushover::setUrl(String url) {
	_url = url;
}
void myPushover::setUrlTitle(String url_title) {
	_url_title = url_title;
}
void myPushover::setPriority(int8_t priority) {
	_priority = priority;
}
void myPushover::setRetry(uint16_t retry) {
	_retry = retry;
}
void myPushover::setExpire(uint16_t expire) {
	_expire = expire;
}
void myPushover::setTimestamp(uint32_t timestamp) {
	_timestamp = timestamp;
}
void myPushover::setSound(String sound) {
	_sound = sound;
}
void myPushover::setTimeout(uint16_t timeout) {
	_timeout = timeout;
}
void myPushover::setHTML(boolean html) {
	_html = html;
}
void myPushover::setDebug(boolean debug) {
	_debug = debug;
}

//------------------------------------------------
int myPushover::send(String &response) {
	WiFiClientSecure client;
	if (!client.connect("api.pushover.net", 443)) {
	    returncode = 3 ;
		return (returncode);
	}
	if (_debug) {
	    Serial.println ("connected to pushover.net");
	}
	String post = String("token=")+_token+"&user="+_user+"&title="+_title+"&message="+_message+"&device="+_device+"&url="+_url+"&url_title="+_url_title+"&priority="+_priority+"&retry="+_retry+"&expire="+_expire+"&sound="+_sound;
	if (_timestamp != 0) post += String("&timestamp=")+_timestamp;
	if (_html == true) post += String("&html=1");
	String http = String("POST /1/messages.json HTTP/1.1\r\nHost: api.pushover.net\r\nConnection: close\r\nAccept: Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nContent-Length: ")+post.length()+"\r\n\r\n"+post;
	client.print(http);
	int timeout_at = millis() + _timeout;
	while (!client.available() && timeout_at - millis() < 0) {
		client.stop();	
		return (4);                         // timeout 
	}
	String line1;
	String line2;


	line1 = client.readStringUntil('\n');
	while (client.available() != 0) {
		if (client.read() == '{') break;
	}
	line2 = client.readStringUntil('\n');
	
    if (_debug) {	
        Serial.print ("line1 : "); Serial.println (line1);
        Serial.print ("line2 : "); Serial.println (line2);
    }
    client.stop();
    
    // line 1 contains HTTP/1.1 400  or HTTP/1.1 200
	int len = line1.length();
	if (len > 20) response = "l1=" + line1.substring(0, 20) + "*" + "\r";	
	else response = "l1=" + line1 + "\r";
	
	// line2 contais description of error
    len = line2.length();
	if (len > 25) response = response  + "l2=" + line2.substring(0, 25) + "\r\n";
	else response = response + "l2=" + line2 + "\r\n";
	
	if (_debug) {
	    Serial.print ("pushover response: ");
	    Serial.println (response);
	  
	}
	
	// check respone and return accordingly
	if ( (line1.indexOf("HTTP/1.1 200") == 0) || (line1.indexOf("\"status\":1") == 0)) return (0);      // ok return
	if ( (line2.indexOf("HTTP/1.1 200") == 0) || (line2.indexOf("\"status\":1") == 0)) return (0);      // ok return	
	
   	if (line1.indexOf("HTTP/1.1 400") == 0) return (2);      // bad request, give back response
	else return (5) ;                                        // any other error


}

