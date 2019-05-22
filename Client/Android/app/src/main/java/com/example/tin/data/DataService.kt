package com.example.tin.data

import com.example.tin.data.entity.Account
import com.example.tin.data.entity.ConsultationInfo
import com.example.tin.dto.request.*
import com.example.tin.dto.response.ConsultationList
import com.example.tin.dto.response.LoginResponse
import com.example.tin.dto.response.NewConsultationResponse
import com.example.tin.dto.response.RegisterResponse
import com.example.tin.network.Connection
import com.fasterxml.jackson.databind.ObjectMapper
import java.lang.ref.WeakReference

object DataService : Connection.NetworkEventListener {

    interface LoginListener {
        fun onLoginSuccess()
        fun onLoginFailure()
    }

    interface RegisterListener {
        fun onRegisterSuccess()
        fun onRegisterFailure()
    }

    interface ConsultationsListener {
        fun updateFreeConsultations(consultations: List<ConsultationInfo>)
    }

    interface MyConsultationsListener {
        fun updateMyReservedConsultations(consultations: List<ConsultationInfo>)
    }

    interface SuggestConsultationListener {
        fun onSuggestSuccess()
        fun onSuggestFailure()
    }

    private val objectMapper = ObjectMapper()
    private var loginListener: WeakReference<LoginListener>? = null
    private var registerListener: WeakReference<RegisterListener>? = null
    private var consultationsListener: WeakReference<ConsultationsListener>? = null
    private var myConsultationsListener: WeakReference<MyConsultationsListener>? = null
    private var suggestConsultationListener: WeakReference<SuggestConsultationListener>? = null

    fun setLoginListener(loginListener: LoginListener) {
        this.loginListener = WeakReference(loginListener)
    }

    fun setRegisterListener(registerListener: RegisterListener) {
        this.registerListener = WeakReference(registerListener)
    }

    fun setConsultationsListener(consultationsListener: ConsultationsListener) {
        this.consultationsListener = WeakReference(consultationsListener)
    }

    fun setMyConsultationsListener(myConsultationsListener: MyConsultationsListener) {
        this.myConsultationsListener = WeakReference(myConsultationsListener)
    }

    fun setSuggestConsultationListener(suggestConsultationListener: SuggestConsultationListener) {
        this.suggestConsultationListener = WeakReference(suggestConsultationListener)
    }

    override fun incomingMessage(message: String) {
        val rootNode = objectMapper.readTree(message)
        when (rootNode.path("type").asText()) {
            "LoginResponse" -> {
                processLoginResponse(message)
            }
            "RegistrationResponse" -> {
                processRegisterResponse(message)
            }
            "DailyConsultationListResponse" -> {
                processConsultationsForDay(message)
            }
            "NewConsultationResponse" -> {
                processSuggestConsultation(message)
            }
        }

    }

    private fun processLoginResponse(message: String) {
        try {
            val loginResponse = objectMapper.readValue(message, LoginResponse::class.java)
            try {
                if (loginResponse.status == 0) {
                    loginListener!!.get()!!.onLoginSuccess()
                } else {
                    loginListener!!.get()!!.onLoginFailure()
                }
            } catch (e: NullPointerException) {

            }
        } catch (e: Exception) {
            println(e)
        }
    }

    private fun processRegisterResponse(message: String) {
        val registerResponse = objectMapper.readValue(message, RegisterResponse::class.java)
        try {
            if (registerResponse.status == 0) {
                registerListener!!.get()!!.onRegisterSuccess()
            } else {
                registerListener!!.get()!!.onRegisterFailure()
            }
        } catch (e: NullPointerException) {

        }
    }

    private fun processConsultationsForDay(message: String) {
        val consultationsResponse = objectMapper.readValue(message, ConsultationList::class.java)

        try {
            consultationsListener!!.get()!!.updateFreeConsultations(consultationsResponse.consultations)
        } catch (e: NullPointerException) {

        }
    }

    private fun processSuggestConsultation(message: String) {
        val suggestionResponse = objectMapper.readValue(message, NewConsultationResponse::class.java)
        try {
            if (suggestionResponse.status == 0) {
                suggestConsultationListener!!.get()!!.onSuggestSuccess()
            } else {
                suggestConsultationListener!!.get()!!.onSuggestFailure()
            }
        } catch (e: NullPointerException) {

        }
    }

    private val connection = Connection

    init {
        connection.setNetworkEventListener(this)
    }


    fun getFreeConsultations(date: Long) {
        connection.sendMessage(objectMapper.writeValueAsString(GetFreeConsultationsForDateRequest(date)))
    }

    fun reserveConsultation(id: String, username: String) {
        connection.sendMessage(
            objectMapper.writeValueAsString(
                ReserveConsultationRequest(
                    id,
                    username
                )
            )
        )
    }

    fun cancelConsultation(id: String, username: String) {
        connection.sendMessage(
            objectMapper.writeValueAsString(
                CancelConsultationRequest(
                    id,
                    username
                )
            )
        )
    }

    fun newConsultation(newConsultationRequest: NewConsultationRequest) {
        connection.sendMessage(objectMapper.writeValueAsString(newConsultationRequest))
    }

    fun getReservedConsultations(username: String) {

    }

    fun register(account: Account) {
        connection.sendMessage(
            objectMapper.writeValueAsString(
                RegisterRequest(
                    account.login,
                    account.login,
                    account.hashedPassword,
                    account.name,
                    account.surname
                )
            )
        )
    }

    fun login(login: String, password: String) {
        connection.sendMessage(
            objectMapper.writeValueAsString(
                LoginRequest(
                    login,
                    password
                )
            )
        )
    }
}