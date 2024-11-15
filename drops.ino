#include <WiFiProvisioner.h> // #include <DNSServer.h>
#include <HTTPClient.h>

WiFiProvisioner::WiFiProvisioner provisioner;
DNSServer dnsServer;

// CONSTANTS
int HOLD_TIME = 3000;
int WAIT_TIME = 5000;
int CONFIRM_TIME = 10000;
// STATES
enum CONNECTION {DISCONNECTED, CONNECTED};
enum STATE {SEND, WAIT, CONFIRMED, IDLE};

enum CONNECTION connection = DISCONNECTED;
const int lastButtonState = 0;
const int buttonState = 0;

// INPUTS & OUTPUTS
const int RLEDPIN = 33;
const int GLEDPIN = 32;
const int BLEDPIN = 26;
const int PUSHBUTTON = 25;
const int RESETBUTTON = 15;

// APP VARIABLES
enum STATE currentState = IDLE;
unsigned long stateStartTime = 0;

// This Setup function is used to initialize everything
void setup() {
  pinMode(RLEDPIN, OUTPUT);
  pinMode(GLEDPIN, OUTPUT);
  pinMode(BLEDPIN, OUTPUT);
  // This statement will declare pin 15 as digital input
  pinMode(PUSHBUTTON, INPUT);
  Serial.begin(9600);

  // Customize the Access Point name and theme color
  provisioner.AP_NAME = "Drops Botão";
  provisioner.HTML_TITLE = "Configuração Drops";
  provisioner.THEME_COLOR = "#0069ff";
  provisioner.PROJECT_TITLE = "Drops";
  provisioner.CONNECTION_SUCCESSFUL = "Conectado com sucesso";
  provisioner.RESET_CONFIRMATION_TEXT = "Tem certeza que deseja resetar a conexão do dispositivo?";
  provisioner.SVG_LOGO = R"rawliteral(<svg width="70%" height="70%" viewBox="0 0 748 257" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" xml:space="preserve" xmlns:serif="http://www.serif.com/" style="fill-rule:evenodd;clip-rule:evenodd;stroke-linejoin:round;stroke-miterlimit:2;">
    <g transform="matrix(1,0,0,1,-1470.63,-411.733)">
        <g id="Principal" transform="matrix(2.00117,0,0,1.10877,-1207.67,0)">
            <rect x="1255.32" y="0" width="539.684" height="974.056" style="fill:none;"/>
            <g transform="matrix(0.36697,0,0,0.662332,1281.12,120.52)">
                <g transform="matrix(0.998596,0,0,1,29.2507,0)">
                    <path d="M227.715,658.052C208.533,658.052 191.308,653.815 176.04,645.34C160.771,636.865 148.766,624.998 140.025,609.739C131.283,594.48 126.913,576.554 126.913,555.961C126.913,535.365 131.283,517.438 140.025,502.181C148.766,486.924 160.771,475.066 176.04,466.606C191.308,458.147 208.533,453.917 227.715,453.917C244.331,453.917 259.227,457.603 272.404,464.973C285.581,472.344 296.045,483.535 303.795,498.545C311.545,513.555 315.42,532.694 315.42,555.961C315.42,579.042 311.678,598.15 304.194,613.284C296.711,628.419 286.387,639.664 273.223,647.019C260.06,654.375 244.89,658.052 227.715,658.052ZM233.249,618.364C244.449,618.364 254.487,615.841 263.362,610.797C272.238,605.753 279.307,598.505 284.568,589.052C289.83,579.599 292.461,568.569 292.461,555.961C292.461,543.105 289.83,532.02 284.568,522.708C279.307,513.395 272.238,506.216 263.362,501.172C254.487,496.128 244.449,493.606 233.249,493.606C222.045,493.606 212.005,496.128 203.13,501.172C194.254,506.216 187.186,513.395 181.926,522.708C176.667,532.02 174.037,543.105 174.037,555.961C174.037,568.569 176.667,579.599 181.926,589.052C187.186,598.505 194.254,605.753 203.13,610.797C212.005,615.841 222.045,618.364 233.249,618.364ZM293.773,655.621L293.773,608.508L295.348,555.635L291.616,502.767L291.616,378.697L338.267,378.697L338.267,655.621L293.773,655.621Z" style="fill:rgb(0,193,229);fill-rule:nonzero;"/>
                </g>
                <g transform="matrix(1.0247,0,0,1,-11.4268,0)">
                    <path d="M399.636,655.621L399.636,456.349L444.13,456.349L444.13,511.106L438.87,495.186C444.655,481.646 454.01,471.382 466.937,464.396C479.863,457.41 495.796,453.917 514.737,453.917L514.737,498.335C512.739,498.055 510.905,497.845 509.235,497.705C507.565,497.565 505.887,497.495 504.199,497.495C486.53,497.495 472.461,502.633 461.992,512.908C451.522,523.183 446.288,538.574 446.288,559.081L446.288,655.621L399.636,655.621Z" style="fill:rgb(0,193,229);fill-rule:nonzero;"/>
                </g>
                <g transform="matrix(3.53514,0,0,3.53514,-516.561,-896.74)">
                    <path d="M338.855,383.319C349.519,387.875 357,398.463 357,410.784C357,427.26 343.624,440.636 327.149,440.636C310.673,440.636 297.297,427.26 297.297,410.784C297.297,398.463 304.778,387.875 315.442,383.319L315.442,396.765C311.433,400.117 308.881,405.155 308.881,410.784C308.881,420.867 317.066,429.052 327.149,429.052C337.231,429.052 345.416,420.867 345.416,410.784C345.416,405.155 342.864,400.117 338.855,396.765L338.855,383.319Z" style="fill:rgb(0,193,229);"/>
                </g>
                <g transform="matrix(0.998596,0,0,1,-17.8724,0)">
                    <path d="M902.141,658.052C885.774,658.052 870.939,654.367 857.636,646.996C844.332,639.625 833.806,628.38 826.058,613.261C818.31,598.142 814.436,579.058 814.436,556.008C814.436,532.674 818.178,513.504 825.662,498.495C833.146,483.487 843.53,472.306 856.816,464.95C870.102,457.595 885.211,453.917 902.141,453.917C921.571,453.917 938.859,458.155 954.003,466.63C969.147,475.105 981.09,486.971 989.831,502.228C998.573,517.485 1002.94,535.411 1002.94,556.008C1002.94,576.605 998.573,594.531 989.831,609.788C981.09,625.045 969.147,636.904 954.003,645.363C938.859,653.823 921.571,658.052 902.141,658.052ZM791.589,728.024L791.589,456.349L836.083,456.349L836.083,503.461L834.508,556.335L838.24,609.202L838.24,728.024L791.589,728.024ZM896.607,618.364C907.811,618.364 917.851,615.841 926.726,610.797C935.602,605.753 942.67,598.512 947.93,589.075C953.19,579.638 955.82,568.616 955.82,556.008C955.82,543.152 953.19,532.059 947.93,522.731C942.67,513.403 935.602,506.216 926.726,501.172C917.851,496.128 907.811,493.606 896.607,493.606C885.407,493.606 875.368,496.128 866.491,501.172C857.613,506.216 850.545,513.403 845.285,522.731C840.025,532.059 837.395,543.152 837.395,556.008C837.395,568.616 840.025,579.638 845.285,589.075C850.545,598.512 857.613,605.753 866.491,610.797C875.368,615.841 885.407,618.364 896.607,618.364Z" style="fill:rgb(0,193,229);fill-rule:nonzero;"/>
                </g>
                <g transform="matrix(0.996326,0,0,1,-20.8904,0)">
                    <path d="M1109.31,658.052C1092.54,658.052 1076.51,655.915 1061.21,651.641C1045.92,647.366 1033.81,642.136 1024.87,635.951L1042.82,600.49C1051.65,606.213 1062.32,610.908 1074.8,614.576C1087.29,618.244 1099.74,620.078 1112.14,620.078C1126.9,620.078 1137.54,618.123 1144.07,614.214C1150.6,610.305 1153.87,604.908 1153.87,598.023C1153.87,592.655 1151.65,588.528 1147.2,585.643C1142.76,582.759 1136.89,580.564 1129.6,579.06C1122.3,577.555 1114.28,576.189 1105.51,574.96C1096.74,573.732 1087.96,572.052 1079.17,569.922C1070.39,567.791 1062.35,564.704 1055.06,560.659C1047.77,556.613 1041.9,551.067 1037.45,544.019C1033.01,536.97 1030.79,527.708 1030.79,516.232C1030.79,503.729 1034.38,492.794 1041.57,483.427C1048.76,474.06 1058.88,466.8 1071.94,461.647C1085,456.494 1100.48,453.917 1118.38,453.917C1131.8,453.917 1145.37,455.448 1159.11,458.509C1172.85,461.571 1184.2,465.854 1193.16,471.359L1175.22,506.82C1165.86,501.097 1156.35,497.179 1146.71,495.064C1137.06,492.949 1127.56,491.891 1118.2,491.891C1104.04,491.891 1093.52,493.97 1086.62,498.128C1079.73,502.286 1076.29,507.667 1076.29,514.272C1076.29,520.073 1078.51,524.477 1082.96,527.486C1087.41,530.495 1093.28,532.861 1100.57,534.583C1107.86,536.305 1115.89,537.78 1124.66,539.006C1133.42,540.233 1142.19,541.92 1150.96,544.068C1159.73,546.216 1167.76,549.258 1175.05,553.194C1182.34,557.131 1188.21,562.568 1192.66,569.508C1197.1,576.447 1199.33,585.546 1199.33,596.805C1199.33,609.214 1195.68,620.002 1188.41,629.169C1181.13,638.336 1170.79,645.442 1157.39,650.486C1143.99,655.53 1127.96,658.052 1109.31,658.052Z" style="fill:rgb(0,193,229);fill-rule:nonzero;"/>
                </g>
                <g transform="matrix(0.67526,0,0,0.966717,320.213,-226.277)">
                    <path d="M473.509,676.205C473.509,676.205 504.481,748.221 504.481,778.46C504.481,790.4 490.603,800.094 473.509,800.094C456.414,800.094 442.536,790.4 442.536,778.46C442.536,748.221 473.509,676.205 473.509,676.205Z" style="fill:rgb(0,193,229);"/>
                </g>
            </g>
        </g>
    </g>
</svg>)rawliteral";

  // Used to reset network connection TODO: Button to enable reset
  // provisioner.resetCredentials();
  provisioner.connectToWiFi();

  // Start the DNS Server and redirect all URLs to the captive portal IP (192.168.4.1)
  // Attempt to automatically open the config page
  // IPAddress apIP(192, 168, 4, 1);
  // dnsServer.start(53, "*", apIP);
}

void loop() {
  // if (connection == DISCONNECTED) {
  //   dnsServer.processNextRequest();
  // }
  unsigned long currentTime = millis();
  int button_state = digitalRead(PUSHBUTTON);

  switch( currentState ){
    case IDLE:
      if ( button_state == HIGH ) {
        unsigned long pressedTime = millis();
        while ( digitalRead(PUSHBUTTON) == HIGH ) {
          if ( millis() - pressedTime > HOLD_TIME ) {
            currentState = SEND;
            stateStartTime = millis();
            Serial.println("State: SEND");
            break;
          }
        }
      }
      analogWrite(RLEDPIN, 255);
      analogWrite(GLEDPIN, 255);
      analogWrite(BLEDPIN, 255);
      break;
    case SEND:
      if (currentTime - stateStartTime >= WAIT_TIME) {
          currentState = WAIT;
          stateStartTime = millis();
          Serial.println("State: WAIT");
      }
      analogWrite(RLEDPIN, 0);
      analogWrite(GLEDPIN, 255);
      analogWrite(BLEDPIN, 0);
      break;
    case WAIT:
      if (currentTime - stateStartTime >= WAIT_TIME) {
          currentState = CONFIRMED;
          stateStartTime = millis();
          Serial.println("State: CONFIRMED");
      }
      analogWrite(RLEDPIN, 255);
      analogWrite(GLEDPIN, 0);
      analogWrite(BLEDPIN, 0);
      break;
    case CONFIRMED:
      if (currentTime - stateStartTime >= CONFIRM_TIME) {
          currentState = IDLE;
          stateStartTime = millis();
          Serial.println("State: IDLE");
      }
      analogWrite(RLEDPIN, 0);
      analogWrite(GLEDPIN, 0);
      analogWrite(BLEDPIN, 255);
      break;
  }
}

void sendRequest() {
  HTTPClient http;

  // Start the HTTP request
  http.begin("https://www.google.com");
  http.addHeader("Content-Type", "application/json");

  // Prepare the JSON payload (modify according to your API requirements)
  String payload = "{\"message\":\"Button pressed!\"}";

  // Send the POST request
  int httpCode = http.POST(payload);

  // Check if the request was successful
  if (httpCode > 0) {
    String response = http.getString();
    Serial.println("Response code: " + String(httpCode));
    Serial.println("Response: " + response);
  } else {
    Serial.println("Error in sending POST request");
  }

  // End the HTTP connection
  http.end();
}
