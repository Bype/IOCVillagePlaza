//import android.net.Uri;
//import android.content.Intent;

class ActivitiesAction extends Sequence
{
  /*
  Uri tUri;
  Intent tIntent;
  */
  boolean played;
  ActivitiesAction(String aUrl)
  {
    super("");
    /*
    tUri = Uri.parse(aUrl);
    tIntent = new Intent(Intent.ACTION_VIEW);
    tIntent.setDataAndType(tUri, "video/*");
    played = false;
    */
  }
  void setup()
  {
    if(!played)
    {
      played = true;
 //     startActivity(tIntent);
    }
  }
 
}

