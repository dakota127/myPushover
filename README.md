# myPushover
Pushover Library for ESP32.

This Lib is based on this lib:
 https://github.com/ArduinoHannover/Pushover
 
 While the referenced lib works just fine, I needed better errorhandling, not just false or true and debugging. The return value is therefore int instead of boolean. There is also an additional Setter to set a debug flag.
 
 Library returns:
 0:         ok message sent, return was HTTP/1.1 200
 2:         return was HTTP/1.1 400, bad request (token/userkey, Message with errors)
 3:         no connection to server api.pushover.net
 4:         timeout
  
 ******************************************************************* 


## Usage
The library offers almost all functions.

Initialize a new Pushover: `myPushover po = myPushover("myAppToken","myUserToken");`

Then you can call the setters and if you're done, just call `po.send()` which will return (int) zero on success.

### Setters
```
void setMessage(String); //required. otherwise it makes no sense, does it?
void setDevice(String); //broadcast to every device! do you really want to set this? ;-)
void setTitle(String); //what it's all about. otherwise app name
void setUrl(String); //oh, you want to open something! no call, no link
void setUrlTitle(String); //if you like to have something different than "Open URL"
void setPriority(int8_t); //-2, -1, 0 (default) 1 and 2
void setRetry(uint16_t); //retry in seconds, must be set with priority of 2
void setExpire(uint16_t); //timeout for message in seconds, must be set with priority of 2
void setTimestamp(uint32_t); //unix timestamp, if not set, it will be the time the message was received
void setSound(String); //pick a nice sound from the list
void setHTML(boolean); //is your message html formatted?
void setDebug(boolean); //give debug output?
```

There is also a setter for the connection timeout (ms): `setTimeout(uint16_t)`.
