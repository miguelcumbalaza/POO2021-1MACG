using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class herz : MonoBehaviour
{
    public Rigidbody2D rb;
    public Animator animator;
    public float velocidad = 5;
    private Vector2 move;
    private void Update()
    {
        move.x = Input.GetAxisRaw( "Horizontal" );
        move.y = Input.GetAxisRaw("Vertical");
        animator.SetFloat("Horizontal", move.x);
        animator.SetFloat("Vertical", move.y);
        animator.SetFloat("Velocidad", move.sqrMagnitude);
    }
    private void FixedUpdate(){
        rb.MovePosition( rb.position + move * velocidad * Time.fixedDeltaTime );
    }
}