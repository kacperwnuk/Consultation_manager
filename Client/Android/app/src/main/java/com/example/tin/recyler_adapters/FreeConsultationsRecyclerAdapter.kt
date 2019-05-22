package com.example.tin.recyler_adapters

import android.annotation.SuppressLint
import android.content.Context
import android.support.constraint.ConstraintLayout
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import com.example.tin.R
import com.example.tin.data.entity.ConsultationInfo
import com.example.tin.data.entity.enums.ConsultationType
import java.text.SimpleDateFormat
import java.util.*

class FreeConsultationsRecyclerAdapter(
    private val consultations: List<ConsultationInfo>,
    private val actionListener: ActionListener
) : RecyclerView.Adapter<RecyclerView.ViewHolder>() {

    private lateinit var context: Context

    interface ActionListener {
        fun addBefore(day: String, consultationDateEnd: String)

        fun addAfter(day: String, consultationDateStart: String)

        fun reserve(id: String)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        context = parent.context
        return when (viewType) {
            0 -> {
                StudentSuggestedRecyclerViewHolder(
                    LayoutInflater.from(parent.context)
                        .inflate(
                            R.layout.student_suggested_consultation_item,
                            parent,
                            false
                        ) as ConstraintLayout
                )
            }
            else -> LecturerSuggestedRecyclerViewHolder(
                LayoutInflater.from(parent.context)
                    .inflate(R.layout.free_consultation_item, parent, false) as ConstraintLayout
            )
        }

    }

    override fun getItemCount(): Int {
        return consultations.size
    }

    @SuppressLint("SetTextI18n")
    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        val consultation = consultations[position]
        holder.itemView.elevation = 20.0f
        holder.itemView.findViewById<TextView>(R.id.person).text =
            "${consultation.lecturer.name} ${consultation.lecturer.surname}"
        holder.itemView.findViewById<TextView>(R.id.room).text = consultation.room
        val (startDate, startTime) = dateToString(consultation.consultationDateStart)
        val (endDate, endTime) = dateToString(consultation.consultationDateEnd)
        var consultationDateEnd = endTime
        holder.itemView.findViewById<TextView>(R.id.day).text = startDate
        when (holder) {
            is LecturerSuggestedRecyclerViewHolder -> {
                holder.itemView.findViewById<TextView>(R.id.start_time).text = "$startTime - $endTime"
                holder.itemView.findViewById<Button>(R.id.reservation_button).setOnClickListener { v ->
                    actionListener.reserve(consultation._id)
                }
            }
            else -> { //student suggested item
                if (consultations.size > 1) {
                    var i = position + 1
                    var j = position
                    if (position > 0 && consultations[position - 1].consultationType == ConsultationType.STUDENT_SUGGESTED
                        && consultations[position - 1].lecturer == consultation.lecturer && consultations[position - 1].consultationDateEnd == consultation.consultationDateStart
                    ) {
                        holder.itemView.visibility = View.GONE
                        holder.itemView.layoutParams = ViewGroup.LayoutParams(0, 0)
                    } else {
                        while (consultations[i].consultationType == ConsultationType.STUDENT_SUGGESTED && i < itemCount) {
                            if (consultations[i].lecturer == consultations[j].lecturer && consultations[i].consultationDateStart == consultations[j].consultationDateEnd) {
                                consultationDateEnd = dateToString(consultations[i].consultationDateEnd).second
                                i++
                                j++
                            } else {
                                break
                            }
                        }
                    }
                    holder.itemView.findViewById<TextView>(R.id.start_time).text = "$startTime - $consultationDateEnd"
                } else {
                    holder.itemView.findViewById<TextView>(R.id.start_time).text = "$startTime - $endTime"
                }
                holder.itemView.findViewById<Button>(R.id.add_after_button).setOnClickListener {
                    actionListener.addAfter(startDate, consultationDateEnd)
                }
                holder.itemView.findViewById<Button>(R.id.add_before_button).setOnClickListener {
                    actionListener.addBefore(startDate, startTime)
                }
            }
        }
    }

    override fun getItemViewType(position: Int): Int {
        return if (consultations[position].consultationType == ConsultationType.STUDENT_SUGGESTED)
            0
        else
            1
    }

    private fun dateToString(date: Long): Pair<String, String> {
        val dateFormat = SimpleDateFormat("yyyy-MM-dd", Locale.ENGLISH)
        val timeFormat = SimpleDateFormat("HH:mm", Locale.ENGLISH)
        return Pair(dateFormat.format(Date(date)), timeFormat.format(Date(date)))
    }

}

class LecturerSuggestedRecyclerViewHolder(item: ConstraintLayout) : RecyclerView.ViewHolder(item)
class StudentSuggestedRecyclerViewHolder(item: ConstraintLayout) : RecyclerView.ViewHolder(item)


