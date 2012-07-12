import android.net.Uri;
import android.content.Intent;

class ActivitiesAction extends Sequence
{
  Uri tUri;
  Intent tIntent;
  boolean played;
  String aFilename;
  ActivitiesAction(String aUrl)
  {
    super("");
    aFilename = aUrl;
    tUri = Uri.parse(aUrl);
    tIntent = new Intent(Intent.ACTION_VIEW);
    tIntent.setDataAndType(tUri, "video/*");
    played = false;
  }
  void setup()
  {
    if (!played)
    {
      played = true;
      startActivity(tIntent);
    }
  }
}

class PDFAction extends ActivitiesAction
{
  PDFAction(String aUrl)
  {
    super("");
    File file = new File(aUrl);
    Uri uri = Uri.fromFile(file);
    tIntent = new Intent(Intent.ACTION_VIEW);
    tIntent.setDataAndType(uri, "application/pdf");
    played = false;
  }
}

