package com.example.tin.dto.response

import com.example.tin.data.entity.ConsultationInfo
import com.fasterxml.jackson.annotation.JsonIgnoreProperties

@JsonIgnoreProperties("type")
class ConsultationList {
    var consultations: List<ConsultationInfo>? = listOf()
}