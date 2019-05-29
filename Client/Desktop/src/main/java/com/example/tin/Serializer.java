package com.example.tin;

import com.example.tin.dto.Consultation;
import com.example.tin.dto.ConsultationsResponse;
import com.example.tin.dto.Participant;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.IOException;

public class Serializer {

    private ConnectionController connectionController = new ConnectionController();

    public void serializeAndSend(Object ob) throws IOException {
        JSONObject obj = new JSONObject(ob);
        connectionController.send(obj.toString());
    }

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

    public ConsultationsResponse deserializeConsultations() throws IOException, JSONException {
        JSONObject obj = new JSONObject(connectionController.receive());
        try{
            ConsultationsResponse response = new ConsultationsResponse();
            JSONArray array = obj.getJSONArray("consultations");
            for (int  i=0; i < array.length(); ++i){
                JSONObject ob = array.getJSONObject(i);
                Consultation con = new Consultation();
                con.setId(ob.getString("id"));
                con.setConsultationDateStart(ob.getLong("consultationDateStart"));
                con.setConsultationDateEnd(ob.getLong("consultationDateEnd"));
                con.setConsultationType(ob.getInt("consultationType"));
                con.setRoom(ob.getInt("room"));
                con.setLecturer(new Participant(ob.getJSONObject("lecturer")));
                con.setStudent(new Participant(ob.getJSONObject("student")));
                response.getConsultations().add(con);
            }
            return response;
        }
        catch(Exception e){
            return null;
        }
    }

    public boolean isConnected(){
        return connectionController.isConnected();
    }

    public void disconnect(){
        connectionController.disconnect();
    }
}
