package com.example.tin.data

import com.example.tin.data.entity.Account
import com.example.tin.dto.request.*
import com.example.tin.dto.response.LoginResponse
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
        fun updateFreeConsultations(consultations: List<Consultation>)
    }

    private val objectMapper = ObjectMapper()
    private var loginListener: WeakReference<LoginListener>? = null
    private var registerListener: WeakReference<RegisterListener>? = null
    private var consultationsListener: WeakReference<ConsultationsListener>? = null

    fun setLoginListener(loginListener: LoginListener) {
        this.loginListener = WeakReference(loginListener)
    }

    fun setRegisterListener(registerListener: RegisterListener) {
        this.registerListener = WeakReference(registerListener)
    }

    fun setConsultationsListener(consultationsListener: ConsultationsListener) {
        this.consultationsListener = WeakReference(consultationsListener)
    }

    override fun incomingMessage(message: String) {
        val rootNode = objectMapper.readTree(message)
        when (rootNode.path("type").asInt()) {
            1 -> {
                processLoginResponse(message)
            }
            2 -> {
                processRegisterResponse(message)
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

    private val connection = Connection

    init {
        connection.setNetworkEventListener(this)
    }


    fun getFreeConsultations(date: Long): List<Consultation> {
        connection.sendMessage(objectMapper.writeValueAsString(GetFreeConsultationsForDateRequest(date)))
        return listOf(
            Consultation(
                "3",
                "Dr. inż. Gawkowski",
                "12.00",
                "12.15",
                "21.03.2019",
                ConsultationType.LECTURER_SUGGESTED
            ),
            Consultation("4", "Dr. inż. Gawkowski", "12.15", "12.30", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation(
                "5",
                "Dr. inż. Gawkowski",
                "12.30",
                "12.45",
                "21.03.2019",
                ConsultationType.LECTURER_SUGGESTED
            ),
            Consultation("6", "Dr. inż. Gawkowski", "12.45", "13.00", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation("7", "Dr. inż. Gawkowski", "16.45", "17.15", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation("8", "Dr. inż. Gawkowski", "17.15", "17.30", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation(
                "9",
                "Dr. inż. Gawkowski",
                "12.00",
                "12.15",
                "22.03.2019",
                ConsultationType.LECTURER_SUGGESTED
            ),
            Consultation(
                "10",
                "Dr. inż. Gawkowski",
                "12.15",
                "12.30",
                "22.03.2019",
                ConsultationType.LECTURER_SUGGESTED
            ),
            Consultation(
                "11",
                "Dr. inż. Gawkowski",
                "12.30",
                "12.45",
                "22.03.2019",
                ConsultationType.LECTURER_SUGGESTED
            ),
            Consultation(
                "12",
                "Dr. inż. Gawkowski",
                "12.45",
                "13.00",
                "22.03.2019",
                ConsultationType.STUDENT_SUGGESTED
            ),
            Consultation(
                "13",
                "Dr. inż. Gawkowski",
                "13.00",
                "13.15",
                "22.03.2019",
                ConsultationType.STUDENT_SUGGESTED
            ),
            Consultation(
                "14",
                "Dr. inż. Gawkowski",
                "13.15",
                "13.30",
                "22.03.2019",
                ConsultationType.LECTURER_SUGGESTED
            )
        )
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

    fun getReservedConsultations(username: String): List<Consultation> {
        return listOf(
//            Consultation("1","Dr. inż. Kozdrowski", "12.00", "12.15", "21.03.2019", ConsultationType.LECTURER_SUGGESTED),
//            Consultation("2","Dr. inż. Kozdrowski", "12.15", "12.30", "21.03.2019", ConsultationType.LECTURER_SUGGESTED)
        )
    }

    fun register(account: Account) {
        connection.sendMessage(
            objectMapper.writeValueAsString(
                RegisterRequest(
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