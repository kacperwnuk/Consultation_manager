import com.fasterxml.jackson.databind.ObjectMapper
import com.google.gson.stream.JsonReader
import entity.User
import java.io.File
import java.io.FileInputStream
import java.net.URL
import java.io.InputStreamReader
import java.security.cert.CertificateException
import java.security.cert.X509Certificate
import java.security.KeyManagementException
import java.security.NoSuchAlgorithmException
import java.security.cert.CertificateFactory
import javax.net.ssl.*
import java.security.KeyStore



class Main {

  companion object {
    @JvmStatic
    fun main(args: Array<String>) {

      val certificateFactory = CertificateFactory.getInstance("X.509")
      val inputStream = FileInputStream("target/classes/pik-ca.crt")
      val certificate = certificateFactory.generateCertificate(inputStream)
      val tmf = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm())
      val ks = KeyStore.getInstance(KeyStore.getDefaultType())
      ks.load(null) // You don't need the KeyStore instance to come from a file.
      ks.setCertificateEntry("caCert", certificate)

      tmf.init(ks)

      var sc: SSLContext? = null
      try {
        sc = SSLContext.getInstance("SSL")
      } catch (e: NoSuchAlgorithmException) {
        e.printStackTrace()
      }

      try {
        sc!!.init(null, tmf.trustManagers, java.security.SecureRandom())
      } catch (e: KeyManagementException) {
        e.printStackTrace()
      }

      val validHosts = object : HostnameVerifier {
        override fun verify(arg0: String, arg1: SSLSession): Boolean {
          return true
        }
      }
      // All hosts will be valid
      HttpsURLConnection.setDefaultHostnameVerifier(validHosts)

      HttpsURLConnection.setDefaultSSLSocketFactory(sc!!.socketFactory)


      val url = URL("https://localhost:8443/register")
      val myConnection = url.openConnection() as HttpsURLConnection
      myConnection.setRequestProperty("User-Agent", "my-rest-app-v0.1")
      myConnection.requestMethod = "GET"
      myConnection.setRequestProperty("Accept", "application/json")
      if (myConnection.responseCode == 200) {
        val responseBody = myConnection.inputStream;
        val responseBodyReader = InputStreamReader(responseBody, "UTF-8")
        val json = responseBodyReader.readText()
        println(json)
        val user = ObjectMapper().readValue(json, User::class.java)
        print(user)
      } else {
      }
    }
  }
}