#include <Arduino.h>

void init_SD(void);
String FileSD(const char*);
void writeSD(String,String);

typedef struct {
  String time="";
  char outA=0;
  char outB=0;
}structDatos;

#define CantBox 10

class XML {
private:
  String inStr;
public:
  static int countBox;
  void read(const char*);
  String readParam(String);
  void writeParam(String, String);
  String returnStr(void);
  void needDatas(structDatos *);
  String needParam(String, String);
};
