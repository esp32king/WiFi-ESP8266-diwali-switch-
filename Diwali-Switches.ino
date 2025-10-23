// created by Krishna Rajput UP61 (Ghazipur)

#include <ESP8266WiFi.h>

#include <ESP8266WebServer.h>

#include <DNSServer.h>

#include <LittleFS.h>



// Wi-Fi AP credentials

const char* ssid = "Diwali Switch";

const char* password = ""; // Open AP



#define DNS_PORT 53

DNSServer dnsServer;                 // Captive portal DNS server

ESP8266WebServer server(80);



// Relay pins

#define RELAY1 5

#define RELAY2 4

#define RELAY3 0

#define RELAY4 2



bool relayState[5] = {0,0,0,0,0};  // Relay states



// HTML page

String htmlPage() {

  String html = R"rawliteral(

<!DOCTYPE html>

<html lang="en">

<head>

<meta charset="UTF-8">

<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">

<title>🚩 Jai Shree Ram 🚩</title>

<style>

:root{

  --bg1:#0b0000; --bg2:#4a0b0b; --glass: rgba(255,255,255,0.08); 

  --accent1:#ffb300; --accent2:#ff6f00;

}

body{margin:0; font-family:'Poppins',sans-serif; background:radial-gradient(circle at bottom,var(--bg1),var(--bg2)); overflow:hidden; color:#fff; text-align:center;}

.heading-wrapper{display:flex; justify-content:center; align-items:center; gap:8px; margin-top:120px;}

h1{font-size:28px;color:var(--accent1);text-shadow:0 0 12px #ffcc80,0 0 36px #ff6f00;animation:glow 2s infinite alternate;}

@keyframes glow{0%{text-shadow:0 0 8px #ffb74d,0 0 28px #ff6f00;}100%{text-shadow:0 0 16px #ffd54f,0 0 46px #ff3d00;}}

.visit-page{font-size:18px;color:var(--accent1);text-shadow:0 0 8px #ffcc80,0 0 24px #ff6f00;cursor:pointer;}

.garland{position:fixed; top:0; left:0; right:0; height:36px; display:flex; justify-content:center; align-items:flex-end; pointer-events:none; z-index:50;}

.light{width:12px; height:16px; margin:0 4px; border-radius:5px; transform-origin:center bottom; animation:blink 2s infinite;}

.light.o{background:#ff9800; box-shadow:0 0 12px #ff9800; animation-delay:0s;} 

.light.y{background:#ffd740; box-shadow:0 0 12px #ffd740; animation-delay:0.2s;} 

.light.r{background:#ff7043; box-shadow:0 0 12px #ff7043; animation-delay:0.4s;}

@keyframes blink{0%{transform:scaleY(1);opacity:0.25;filter:blur(0.5px);}50%{transform:scaleY(1.3);opacity:1;filter:blur(0);}100%{transform:scaleY(1);opacity:0.25;filter:blur(0.5px);}}

.grid{display:flex; flex-wrap:wrap; justify-content:center; gap:12px; padding:20px 6px 50px; position:relative; z-index:10;}

.relay-card{width:90%; max-width:280px; min-height:110px; padding:16px; border-radius:16px; background:var(--glass); backdrop-filter:blur(8px) saturate(120%); box-shadow:0 6px 18px rgba(0,0,0,0.5),inset 0 1px 0 rgba(255,255,255,0.03); display:flex; flex-direction:column; align-items:center; justify-content:center;}

.relay-card h3{margin:6px 0;color:#ffdcb2; font-size:18px;}

button{width:130px;height:44px;border-radius:10px;border:none;font-size:16px;cursor:pointer;}

.on-btn{background:linear-gradient(180deg,#003d00,#00b248); color:#e6ffe6; box-shadow:0 6px 20px rgba(0,178,72,0.16);}

.off-btn{background:linear-gradient(180deg,#330000,#ff4040); color:#fff0f0; box-shadow:0 6px 20px rgba(255,64,64,0.16);}

.status{margin-top:8px;color:#fff9c4;font-weight:600;font-size:14px;}

footer{position:fixed; bottom:0; width:100%; text-align:center; font-size:14px; color:#ffecb3; text-shadow:0 0 8px #ff8f00; z-index:10; background: rgba(0,0,0,0.3); padding:8px 0;}

footer a{color:var(--accent1); text-decoration:none;}

.diya{position:fixed; bottom:-120px; width:40px; height:60px; border-radius:0 0 25px 25px; background:radial-gradient(ellipse at center,#8b4a2b 30%,#5d4037 100%); box-shadow:0 0 20px #ff9800; animation:floatDiya linear infinite; z-index:1;}

.diya .flame{position:absolute; top:-25px; left:50%; width:14px; height:28px; background:radial-gradient(circle at 50% 60%,#fff176 18%,#ff6f00 60%); border-radius:50%; transform:translateX(-50%); animation:flicker 0.18s infinite alternate; filter:blur(0.8px);}

@keyframes floatDiya{0%{transform:translateY(0);}100%{transform:translateY(-105vh);}}

@keyframes flicker{0%{transform:translateX(-50%) scaleY(1);opacity:.85;}100%{transform:translateX(-48%) scaleY(1.12);opacity:1;}}

.firework{position:fixed; width:5px; height:90px; bottom:0; border-radius:3px; background:linear-gradient(to top,#ffd740,#ff6f00,#fff); opacity:0.9; animation:shoot linear infinite; z-index:1;}

@keyframes shoot{0%{transform:translateY(0);opacity:1;}70%{transform:translateY(-500px);opacity:1;}100%{transform:translateY(-700px);opacity:0;}}

.f1{left:10%; animation-duration:3s;} .f2{left:40%; animation-duration:3.5s;} .f3{left:70%; animation-duration:4s;} .f4{left:85%; animation-duration:3.2s;}

</style>

</head>

<body>

<div class="heading-wrapper">

  <h1>🚩 जय श्री राम 🚩</h1>

</div>

<div class="garland">)rawliteral";



for(int i=0;i<25;i++){

  String cls=(i%3==0)?"light o":((i%3==1)?"light y":"light r");

  html+="<div class='"+cls+"'></div>";

}



html+=R"rawliteral(

</div>

<div class="grid">

<div class="relay-card"><h3>cracker 🧨</h3><button id="btn1" onclick="toggleRelay(1)">Loading...</button><div id="st1" class="status"></div></div>

<div class="relay-card"><h3>Lights</h3><button id="btn2" onclick="toggleRelay(2)">Loading...</button><div id="st2" class="status"></div></div>

<div class="relay-card"><h3>Fan</h3><button id="btn3" onclick="toggleRelay(3)">Loading...</button><div id="st3" class="status"></div></div>

<div class="relay-card"><h3>Room</h3><button id="btn4" onclick="toggleRelay(4)">Loading...</button><div id="st4" class="status"></div></div>

<div class="relay-card"><h3>All Switches</h3><button id="btn5" onclick="toggleAll()">Loading...</button><div id="st5" class="status"></div></div>

</div>

<div class="diya d1" style="animation-duration:12s; left:5%;"><div class="flame"></div></div>

<div class="diya d2" style="animation-duration:14s; left:25%;"><div class="flame"></div></div>

<div class="diya d3" style="animation-duration:11s; left:50%;"><div class="flame"></div></div>

<div class="diya d4" style="animation-duration:13s; left:75%;"><div class="flame"></div></div>

<div class="firework f1"></div>

<div class="firework f2"></div>

<div class="firework f3"></div>

<div class="firework f4"></div>
<marquee>🚩 जय श्री राम 🚩</marquee>
<footer>

Made By KR$HNA 🧨 Diwali Edition 2025 🕉 — 

<a href="https://github.com/esp32king" target="_blank">Visit My GitHub</a>

</footer>

<script>

function updateStatus(){

  fetch('/status').then(r=>r.json()).then(data=>{

    for(let i=1;i<=4;i++){

      let btn=document.getElementById('btn'+i);

      let st=document.getElementById('st'+i);

      if(data['relay'+i]){

        btn.textContent='Turn OFF';

        btn.className='off-btn';

        st.textContent='Status: ON';

      }else{

        btn.textContent='Turn ON';

        btn.className='on-btn';

        st.textContent='Status: OFF';

      }

    }

    let allOn = data['relay1'] && data['relay2'] && data['relay3'] && data['relay4'];

    let btn5 = document.getElementById('btn5');

    let st5 = document.getElementById('st5');

    if(allOn){

      btn5.textContent='Turn All OFF';

      btn5.className='off-btn';

      st5.textContent='Status: ALL ON';

    }else{

      btn5.textContent='Turn All ON';

      btn5.className='on-btn';

      st5.textContent='Status: SOME/OFF';

    }

  });

}

function toggleRelay(id){fetch('/toggle?relay='+id).then(()=>updateStatus());}

function toggleAll(){fetch('/toggle?relay=all').then(()=>updateStatus());}

window.onload=function(){updateStatus(); setInterval(updateStatus,1200);}

</script>

</body>

</html>

)rawliteral";



  return html;

}



// Web handlers

void handleRoot(){ server.send(200,"text/html",htmlPage()); }



void handleStatus(){

  String json="{";

  for(int i=1;i<=4;i++){

    json+="\"relay"+String(i)+"\":"+(relayState[i]?"true":"false");

    if(i<4) json+=",";

  }

  json+="}";

  server.send(200,"application/json",json);

}



void handleToggle(){

  if(!server.hasArg("relay")){server.send(400,"text/plain","Missing relay arg"); return;}

  String arg = server.arg("relay");

  if(arg=="all"){

    for(int r=1;r<=4;r++){

      relayState[r] = !relayState[r];

      int pin = (r==1?RELAY1:r==2?RELAY2:r==3?RELAY3:RELAY4);

      digitalWrite(pin, relayState[r]?LOW:HIGH);

    }

  } else {

    int r = arg.toInt();

    if(r>=1&&r<=4){

      relayState[r]=!relayState[r];

      int pin=(r==1?RELAY1:r==2?RELAY2:r==3?RELAY3:RELAY4);

      digitalWrite(pin,relayState[r]?LOW:HIGH);

    }

  }

  handleStatus();

}



// Redirect all unknown requests to root (for captive portal)

void handleNotFound(){

  server.sendHeader("Location", "/");

  server.send(302, "text/plain", "");

}



void setup(){

  Serial.begin(115200);

  if(!LittleFS.begin()){ Serial.println("LittleFS mount failed"); } else{ Serial.println("LittleFS mounted"); }



  pinMode(RELAY1,OUTPUT); pinMode(RELAY2,OUTPUT); pinMode(RELAY3,OUTPUT); pinMode(RELAY4,OUTPUT);

  digitalWrite(RELAY1,HIGH); digitalWrite(RELAY2,HIGH); digitalWrite(RELAY3,HIGH); digitalWrite(RELAY4,HIGH);



  // Open AP

  WiFi.softAP(ssid);

  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  Serial.print("AP IP: "); Serial.println(WiFi.softAPIP());



  server.on("/",handleRoot);

  server.on("/status",handleStatus);

  server.on("/toggle",handleToggle);

  server.onNotFound(handleNotFound); // <-- ensures captive portal redirect

  server.begin(); Serial.println("HTTP server started");

}



void loop(){

  server.handleClient();

  dnsServer.processNextRequest();

}
