class GPS
{
  public:
    GPS(int RXpin, int TXpin, uint32_t baudRate);
    void dot();
    void dash();
  private:
    int _pin;
};
