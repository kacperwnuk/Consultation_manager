package com.example.tin.dto.request

class NewConsultationRequest(
    val consultationCreatorLogin: String,
    val consultationDateStart: Long,
    val consultationDateEnd: Long,
    val room: String,
    val consultationType: Int = 0,
    val type: String = "NewConsultationRequest"
) {
}