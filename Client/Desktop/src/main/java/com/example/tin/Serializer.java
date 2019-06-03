package com.example.tin;

import com.example.tin.dto.*;
import com.example.tin.entity.Consultation;
import com.example.tin.entity.ConsultationStatus;
import com.example.tin.entity.Participant;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.IOException;
import java.util.List;

public class Serializer {

    private ConnectionController connectionController = new ConnectionController();


    public Serializer()
    {
        ustalKlucz();

    }

    public void ustalKlucz() {
        try {
            serializeAndSend(new KeyRequest());
            KeyResponse response = deserializeKeyResponse();
            if(response.isValid())
            {
                serializeAndSend(new KeyConfirmationRequest());
                connectionController.setKey(response.getKey());
                if(deserialize()) {
                    System.out.println("!!!Poprawnie ustalono klucz!");
                }
            }
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }




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

    public LoginResponse deserializeLoginResponse() throws IOException, JSONException {
        JSONObject obj = new JSONObject(connectionController.receive());
        try{
            if (obj.getInt("status") == 0)
                return new LoginResponse(true, obj.getInt("role") == 1);
        }
        catch(Exception e){
            return new LoginResponse(false);
        }
        return new LoginResponse(false);
    }

    public KeyResponse deserializeKeyResponse() throws Exception {
        JSONObject obj = new JSONObject(connectionController.receive());
        try{
            String key = obj.getString("key");
            if (key.length() == 32)
                return new KeyResponse(true, key);
        }
        catch(Exception e){
            return new KeyResponse(false, "");
        }
        return new KeyResponse(false, "");
    }

    public ConsultationsResponse deserializeConsultations() throws IOException, JSONException {
        JSONObject obj = new JSONObject(connectionController.receive());
        try{
            ConsultationsResponse response = new ConsultationsResponse();
            JSONArray array = obj.getJSONArray("consultations");
            fillConsultations(response.getConsultations(), array);
            return response;
        }
        catch(Exception e){
            return null;
        }
    }

    public UnconfirmedConsultationsResponse deserializeUnconfirmedConsultations() throws IOException, JSONException {
        JSONObject obj = new JSONObject(connectionController.receive());
        try{
            UnconfirmedConsultationsResponse response = new UnconfirmedConsultationsResponse();
            JSONArray array = obj.getJSONArray("consultations");
            fillConsultations(response.getConsultations(), array);
            return response;
        }
        catch(Exception e){
            return null;
        }
    }

    public InactiveUsersResponse deserializeInactiveUsersResponse() throws IOException, JSONException {
        JSONObject obj = new JSONObject(connectionController.receive());
        try{
            InactiveUsersResponse response = new InactiveUsersResponse();
            JSONArray array = obj.getJSONArray("inactiveUsers");
            fillParticipantList(response.getInactiveAccounts(), array);
            return response;
        }
        catch(Exception e){
            return null;
        }
    }

    public AllTutorsResponse deserializeAllTutorsResponse() throws IOException, JSONException {
        JSONObject obj = new JSONObject(connectionController.receive());
        try{
            AllTutorsResponse response = new AllTutorsResponse();
            JSONArray array = obj.getJSONArray("tutors");
            fillParticipantList(response.getTutorsAccounts(), array);
            return response;
        }
        catch(Exception e){
            return null;
        }
    }

    private void fillParticipantList(List<Participant> accountsList, JSONArray array) throws JSONException {
        for (int  i=0; i < array.length(); ++i){
            JSONObject ob = array.getJSONObject(i);
            Participant user = new Participant();
            user.setLogin(ob.getString("login"));
            user.setName(ob.getString("name"));
            user.setSurname(ob.getString("surname"));
            accountsList.add(user);
        }
    }

    private void fillConsultations(List<Consultation> consultationsList, JSONArray array) throws JSONException {
        for (int  i=0; i < array.length(); ++i){
            JSONObject ob = array.getJSONObject(i);
            Consultation con = new Consultation();
            con.setId(ob.getString("_id"));
            con.setConsultationDateStart(ob.getLong("consultationDateStart"));
            con.setConsultationDateEnd(ob.getLong("consultationDateEnd"));
            con.setConsultationType(ob.getInt("consultationType"));
            con.setRoom(ob.getInt("room"));
            con.setStatus(ConsultationStatus.values()[ob.getInt("consultationStatus")]);
            con.setLecturer(new Participant(ob.getJSONObject("lecturer")));
            con.setStudent(new Participant(ob.getJSONObject("student")));
            consultationsList.add(con);
        }
    }

    public boolean isConnected(){
        return connectionController.isConnected();
    }

    public void disconnect(){
        System.out.println("disconnecting");connectionController.disconnect();
    }
}
