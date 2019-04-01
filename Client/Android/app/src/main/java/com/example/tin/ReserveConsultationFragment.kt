package com.example.tin


import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.example.tin.data.Consultation
import com.example.tin.data.ConsultationType
import kotlinx.android.synthetic.main.fragment_reserve_consultation.view.*


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 * Use the [ReserveConsultationFragment.newInstance] factory method to
 * create an instance of this fragment.
 *
 */
class ReserveConsultationFragment : Fragment(), FreeConsultationsRecyclerAdapter.ActionListener {
    // TODO: Rename and change types of parameters
    private var param1: String? = null
    private var param2: String? = null

    private lateinit var recyclerAdapter: RecyclerView.Adapter<RecyclerView.ViewHolder>

    private val consultations = listOf(
        Consultation("Dr. inż. Gawkowski", "12.00", "12.15", "21.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "12.15", "12.30", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "12.30", "12.45", "21.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "12.45", "13.00", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "16.45", "17.15", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "17.15", "17.30", "21.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "12.00", "12.15", "22.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "12.15", "12.30", "22.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "12.30", "12.45", "22.03.2019", ConsultationType.LECTURER_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "12.45", "13.00", "22.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "13.00", "13.15", "22.03.2019", ConsultationType.STUDENT_SUGGESTED),
        Consultation("Dr. inż. Gawkowski", "13.15", "13.30", "22.03.2019", ConsultationType.LECTURER_SUGGESTED)
    )

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        arguments?.let {
            param1 = it.getString(ARG_PARAM1)
            param2 = it.getString(ARG_PARAM2)
        }
        recyclerAdapter = FreeConsultationsRecyclerAdapter(consultations.sortedWith (compareBy ({it.day}, {it.startTime})), this)
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_reserve_consultation, container, false)
        view.recyclerView.apply {
            setHasFixedSize(true)
            adapter = recyclerAdapter
            layoutManager = LinearLayoutManager(context)
        }
        return view
    }

    override fun addBefore(day:String, endTime: String) {
        (context as ActionListener).addBefore(day, endTime)
    }

    override fun addAfter(day: String, startTime: String) {
        (context as ActionListener).addAfter(day, startTime)
    }

    override fun reserve() {
        (context as ActionListener).reserve()
    }

    interface ActionListener {
        fun addBefore(day: String, endTime: String)

        fun addAfter(day: String, startTime: String)

        fun reserve()
    }

    companion object {
        /**
         * Use this factory method to create a new instance of
         * this fragment using the provided parameters.
         *
         * @param param1 Parameter 1.
         * @param param2 Parameter 2.
         * @return A new instance of fragment reserve_consultation.
         */
        // TODO: Rename and change types and number of parameters
        @JvmStatic
        fun newInstance(param1: String, param2: String) =
            ReserveConsultationFragment().apply {
                arguments = Bundle().apply {
                    putString(ARG_PARAM1, param1)
                    putString(ARG_PARAM2, param2)
                }
            }
    }
}
