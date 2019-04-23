import java.net.URL
import javax.net.ssl.HttpsURLConnection
import java.io.InputStreamReader



fun main() {
    val url = URL("https://localhost/register")
    val myConnection = url.openConnection() as HttpsURLConnection
    myConnection.setRequestProperty("User-Agent", "my-rest-app-v0.1")
    myConnection.setRequestProperty("Accept",
        "application/json")
    if (myConnection.responseCode == 200) {
        val responseBody = myConnection.inputStream;
        val responseBodyReader = InputStreamReader(responseBody, "UTF-8")
        val jsonReader = JsonReader(responseBodyReader)
    } else {
    }
}