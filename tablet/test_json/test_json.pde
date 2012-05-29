import org.json.*;

try {
  // Get the JSON formatted response
  String response = loadStrings( "http://192.168.1.79:800/figures" )[0];

  // Make sure we got a response.
  if ( response != null ) {
    // Initialize the JSONObject for the response
    JSONObject root = new JSONObject( response );

    // Get the "condition" JSONObject
    
    // Get the "temperature" value from the condition object
    int nb = root.getInt("community_dev");

    // Print the temperature
    println( nb );
  }
}
catch (org.json.JSONException e) {
  // do whatever
}

