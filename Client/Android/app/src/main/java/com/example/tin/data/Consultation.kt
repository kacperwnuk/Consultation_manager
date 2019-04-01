package com.example.tin.data

class Consultation(val person: String, val startTime: String, var endTime: String, val day: String, val type: ConsultationType)

enum class ConsultationType {
    STUDENT_SUGGESTED,
    LECTURER_SUGGESTED
}