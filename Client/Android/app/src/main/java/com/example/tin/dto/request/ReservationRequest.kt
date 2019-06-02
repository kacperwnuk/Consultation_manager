package com.example.tin.dto.request

class ReservationRequest(
    val id: String,
    val login: String,
    val type: String = "ConsultationReservationRequest"
) {
}