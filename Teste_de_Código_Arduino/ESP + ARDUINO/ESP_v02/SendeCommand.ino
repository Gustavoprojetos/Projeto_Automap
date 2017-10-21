String SendCommand(String command, const int timeout, boolean debug) 
{
    String response = "";
    wifi.print(command);
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(wifi.available())
      {
        char c = wifi.read();
        response+=c;
      }  
    }
    
    if(debug) {
      Serial.print(response);
    }
    return response;
}
