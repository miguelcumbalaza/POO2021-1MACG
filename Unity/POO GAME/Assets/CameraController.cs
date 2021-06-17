using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    private Transform target;
    private float minX = -1.89f, minY = -14.23f, maxX = 9.87f, maxY = 0.25f;
    private void Start(){
        target = GameObject.FindGameObjectWithTag( "Player" ).GetComponent<Transform>();
    }
    private void LateUpdate(){
        //Mover la camara a la posicion del jugador
        transform.position = new Vector3( target.position.x, target.position.y, transform.position.z );
        //Limitar el rango de la camara
        transform.position = new Vector3( Mathf.Clamp( transform.position.x, minX, maxX ), Mathf.Clamp( transform.position.y, minY, maxY ), transform.position.z );
    }
}
