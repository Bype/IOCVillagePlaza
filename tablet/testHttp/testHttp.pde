void setup()
{
  size(400, 400);
  TestHttpGet mytest = new TestHttpGet();
  try
  {
    mytest.executeHttpGet();
  }
  catch (Exception e) {
    e.printStackTrace();
  }
}
void loop()
{
}

