package com.example.tin.data

import android.app.Activity
import android.content.Context
import android.content.IntentSender
import android.util.Log
import com.google.android.gms.auth.api.credentials.*
import com.google.android.gms.common.api.ResolvableApiException
import com.google.android.gms.tasks.OnCompleteListener
import java.io.Serializable


class CredentialsManager(val context: Context): Serializable {

    private var mCredentialsClient: CredentialsClient

    init {
        val options = CredentialsOptions.Builder().forceEnableSaveDialog().build()
        mCredentialsClient = Credentials.getClient(context, options)
    }

    fun attemptAutoLogin() {
        val mCredentialRequest = CredentialRequest.Builder()
            .setPasswordLoginSupported(true)
            .build()
        mCredentialsClient.request(mCredentialRequest).addOnCompleteListener(
            OnCompleteListener { task ->
                if (task.isSuccessful) {
                    // See "Handle successful credential requests"
                    val retrievedCredential: Credential? = task.result!!.credential
                    if (retrievedCredential != null) {
                        (context as RetrieveCredentialsListener)
                            .login(retrievedCredential)
                    }
                    return@OnCompleteListener
                }
            })
        return
    }

    fun saveCredentials(mEmail: String, mPassword: String) {
        val credential = Credential.Builder(mEmail)
            .setPassword(mPassword)
            .build()
        mCredentialsClient.save(credential).addOnCompleteListener { task ->
            if (task.isSuccessful) {
                Log.d("Save", "SAVE: OK")
                return@addOnCompleteListener
            }

            val e = task.exception
            if (e is ResolvableApiException) {
                // Try to resolve the save request. This will prompt the user if
                // the credential is new.
                val rae = e as ResolvableApiException?
                try {
                    rae!!.startResolutionForResult(context as Activity?, 1)
                } catch (e: IntentSender.SendIntentException) {
                    // Could not resolve the request
                    Log.e("SAVE", "Failed to send resolution.", e)
                }
            } else {
                // Request has no resolution
            }
        }
    }

    fun deleteCredentials(credential: Credential?) {
        if (credential != null) {
            mCredentialsClient.delete(credential).addOnCompleteListener { task ->
                if (task.isSuccessful) {
                    // Credential deletion succeeded.
                    // ...
                    //
                }
            }
        }
    }

    interface RetrieveCredentialsListener {
        fun login(credential: Credential)
    }
}