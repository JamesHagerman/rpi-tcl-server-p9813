import processing.net.*; 
Client myClient;
String colors = "";
int led_count = 50;
float angle = 0;

void setup() {
  myClient = new Client(this, "192.168.25.200", 3333); 
  
}

void draw() {
  colorMode(HSB, 1.0);
  colors = "";
  angle += 5;
  if (angle > 360.0) {
    angle = 0;
  }
  
  String color_string = hex(color(angle/360.0, 1.0, 1.0), 6);
  
  for (int i = 0; i < led_count; i += 1) {
   colors = colors + color_string + " ";
  } 
 
  //print("angle:" + angle);
  //println(" color: " + color_string);
  background(color(angle/360.0, 1.0, 1.0)); 
  myClient.write(colors);
  delay(1); 
}
