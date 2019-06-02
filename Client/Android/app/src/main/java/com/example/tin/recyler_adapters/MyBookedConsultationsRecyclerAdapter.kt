package com.example.tin.recyler_adapters

import android.annotation.SuppressLint
import android.support.constraint.ConstraintLayout
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.ViewGroup
import com.example.tin.R
import com.example.tin.data.entity.ConsultationInfo
import kotlinx.android.synthetic.main.my_booked_consultation_item.view.*
import java.text.SimpleDateFormat
import java.util.*

class MyBookedConsultationsRecyclerAdapter(
    private val consultations: List<ConsultationInfo>,
    private val actionListener: ActionListener
) : RecyclerView.Adapter<RecyclerView.ViewHolder>() {

    interface ActionListener {
        fun cancelConsultation(id: String)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        val item = LayoutInflater.from(parent.context)
            .inflate(R.layout.my_booked_consultation_item, parent, false) as ConstraintLayout
        return MyBookedConsultationRecyclerViewHolder(item)
    }

    override fun getItemCount(): Int {
        return consultations.size
    }

    @SuppressLint("SetTextI18n")
    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        val consultation = consultations[position]
        val (startDate, startTime) = dateToString(consultation.consultationDateStart)
        val (endDate,  endTime) = dateToString(consultation.consultationDateEnd)
        holder.itemView.elevation = 20.0f
        holder.itemView.person.text = "${consultation.lecturer.name} ${consultation.lecturer.surname}"
        holder.itemView.day.text = startDate
        holder.itemView.start_time.text = "$startTime - $endTime"
        holder.itemView.room.text = consultation.room
        holder.itemView.cancellation_button.setOnClickListener { v ->
            actionListener.cancelConsultation(consultation._id)
        }
    }

    private fun dateToString(date: Long): Pair<String, String> {
        val dateFormat = SimpleDateFormat("yyyy-MM-dd", Locale.ENGLISH)
        val timeFormat = SimpleDateFormat("HH:mm", Locale.ENGLISH)
        return Pair(dateFormat.format(Date(date)), timeFormat.format(Date(date)))
    }
}

class MyBookedConsultationRecyclerViewHolder(item: ConstraintLayout) : RecyclerView.ViewHolder(item)