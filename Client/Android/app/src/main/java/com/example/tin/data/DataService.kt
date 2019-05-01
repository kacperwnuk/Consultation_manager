package com.example.tin.data

import android.content.Context
import com.example.tin.data.entity.Account

class DataService(context: Context) {


    fun getFreeConsultations(): List<Consultation> {
        return listOf(
            Consultation("3","Dr. inż. Gawkowski", "12.00", "12.15", "21.03.2019", ConsultationType.LECTURER_SUGGESTED),
            Consultation("4","Dr. inż. Gawkowski", "12.15", "12.30", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation("5","Dr. inż. Gawkowski", "12.30", "12.45", "21.03.2019", ConsultationType.LECTURER_SUGGESTED),
            Consultation("6","Dr. inż. Gawkowski", "12.45", "13.00", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation("7","Dr. inż. Gawkowski", "16.45", "17.15", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation("8","Dr. inż. Gawkowski", "17.15", "17.30", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation("9","Dr. inż. Gawkowski", "12.00", "12.15", "22.03.2019", ConsultationType.LECTURER_SUGGESTED),
            Consultation("10","Dr. inż. Gawkowski", "12.15", "12.30", "22.03.2019", ConsultationType.LECTURER_SUGGESTED),
            Consultation("11","Dr. inż. Gawkowski", "12.30", "12.45", "22.03.2019", ConsultationType.LECTURER_SUGGESTED),
            Consultation("12","Dr. inż. Gawkowski", "12.45", "13.00", "22.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation("13","Dr. inż. Gawkowski", "13.00", "13.15", "22.03.2019", ConsultationType.STUDENT_SUGGESTED),
            Consultation("14","Dr. inż. Gawkowski", "13.15", "13.30", "22.03.2019", ConsultationType.LECTURER_SUGGESTED)
        )
    }

    fun reserveConsultation(id: String, username: String): Boolean {
        return true
    }

    fun cancelConsultation(id: String, username: String): Boolean {
        return true
    }

    fun getReservedConsultations(username: String): List<Consultation> {
        return listOf(
            Consultation("1","Dr. inż. Kozdrowski", "12.00", "12.15", "21.03.2019", ConsultationType.LECTURER_SUGGESTED),
            Consultation("2","Dr. inż. Kozdrowski", "12.15", "12.30", "21.03.2019", ConsultationType.LECTURER_SUGGESTED)
        )
    }

    fun register(account: Account): Boolean {
        return true
    }
}