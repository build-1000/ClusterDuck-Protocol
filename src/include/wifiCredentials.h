#ifndef WIFIPAGE_H
#define WIFIPAGE_H

const char wifi_page[] PROGMEM = R"=====(


   <!DOCTYPE html><html><head><title>Update WiFi Credentials</title>
              <style type="text/css">

      body{
        padding:4em;
      }        
     
      .main-box{
        padding:2em;
        font: 26px "Avenir", helvetica, sans-serif;
        border-radius: 8px;
        background-color: lightgray; 

      }
      .submit {
        border-style: none;
        padding: 0,6em;
        border-radius: 8px;
        background: yellow;
        font-size: 1em; 
        margin-bottom: 3em;

      
      }
      input{
        width:100%; 
        height: 3em;  
        font-size: 1.4em;
      }
   
      
    </style></head><body>

    
     <div class="main-box">
     <h1>Use this page to update your WiFi credentials</h1>
    <p>Fill in your SSID and WiFi Password from your local network below.</p>
 <form action='/changeSSID' method='post'>
    <label for='ssid'>SSID:</label><br> 
    <input name='ssid' type='text' placeholder='SSID' /><br><br>
    <label for='pass'>Password:</label><br>
    <input name='pass' type='text' placeholder='Password' /><br><br>
    <input class="submit" type='submit' value='Submit' />
 </form>
 
   
      </div>

  </body></html>
  
)=====";

#endif