package com.example.tin;

import org.json.JSONException;
import org.json.JSONObject;
import java.io.IOException;

public class Serializer {

    private ConnectionController connectionController = new ConnectionController();

    public void serializeAndSend(Object ob) throws IOException {
        JSONObject obj = new JSONObject(ob);
        connectionController.send(obj.toString());
    }

    /*public String deserialize() throws IOException {
        return connectionController.receive();
    }
    */
    public boolean deserialize() throws IOException, JSONException {
        JSONObject obj = new JSONObject(connectionController.receive());
        try{
            if (obj.getInt("status") == 0)
                return true;
        }
        catch(Exception e){
            return false;
        }
        return false;
    }
}
