[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7421586&assignment_repo_type=AssignmentRepo)

# Carry-My-Luggage
## Índice
- [Objetivo principal](#Objetivo-principal)
- [Recorrido](#Recorrido)
- [Mapa](#Mapa)
- [Reglas y comentarios adicionales](#Reglas-y-comentarios-adicionales)
- [Instrucciones del árbitro](#Instrucciones-del-árbitro)
- [Instrucciones del CO](#Instrucciones-del-CO)
- [Hoja de puntuacion](#Hoja-de-puntuacion)
- [Penalizaciones por no asistir](#Penalizaciones-por-no-asistir)

## Objetivo principal
En esta prueba, el robot tendrá que entrar a la arena en busca de Jhon y acompañarle hacia el coche llevando
la maleta que este elija.

## Recorrido
1. El robot empezará en el punto de inicio y tendrá que entrar dentro de la arena.
2. Dentro de la arena, moverse a la localización del arbitro.
3. El arbitro, mediante su dedo o la voz, indicará que bolsa quiere y el robot tendrá que acercarse a ella.
4. El robot tendrá que pedir que le pongan la bolsa encima y que le indiquen cuando empezar el seguimiento.
5. El robot tendrá que seguir al arbitro por la arena, donde habrá obstáculos.
6. El robot tendrá que seguir al arbitro por fuera de la arena hasta que este se lo indique.
7. El robot tendrá que volver a la arena.

## Mapa

![image](https://user-images.githubusercontent.com/90789825/167892994-1f50b760-7dce-4261-bd97-8b6a32fdb1a3.png)

## Reglas y comentarios adicionales
1. **Deus ex Machina:** Reducción de puntaje por solicitar asistencia humana.
   - Entrega de la bolsa. **Penalty:** -100pts.
   - Encontrar al operador mientras la sigue:
     - Interacción natural (por ejemplo, saludar o llamar). **Penalty:** -100pts.
     - Interacción no natural (por ejemplo, levantar ambas manos o saltar). **Penalty:** -200pts.
     - Tocar el robot (por ejemplo, tirar de la mano del robot). **Penalty:** -400pts.
2. **Obstáculos:** El robot se enfrentará a 4 obstáculos en su camino en cualquier orden:
   A. Una multitud obstruyendo el camino.
   B. Un pequeño objeto en el suelo.
   C. Un objeto 3D difícil de ver.
   D. Una pequeña área bloqueada con barreras retráctiles.
3. **Localización del Coche:** No hay coche afuera. En cambio, se supone que una ubicación fija es una ubicación de automóvil fuera de la arena.
4. **Alcanzar el Coche:** El robot puede llegar a la ubicación del automóvil solo siguiendo al operador.
5. **Siguiendo al operador:** El robot debe indicar al operador cuando está listo para
seguir. El operador camina con naturalidad hacia el coche. Después de llegar al coche, el operador
le quita la bolsa al robot y le agradece.
## Instrucciones del árbitro
Los árbitros necesitan:
- Seleccione un voluntario como operador.
- Seleccione de tres a cuatro personas para obstruir el camino del robot afuera.
- Elija las posiciones de las maletas y asigne una maleta al operador.
- Elija a qué obstáculos se enfrentará el robot en el exterior mientras sigue al operador.
- Elige la ubicación del coche.
- Cuidado con el robot cuando salga de la arena.
## Instrucciones del CO
2h antes del test:
- Seleccione y anuncie el punto de partida del robot.
- Seleccione qué maletas se utilizarán.
## Hoja de puntuacion
El tiempo máximo para esta prueba es de 5 minutos.

![image](https://user-images.githubusercontent.com/90789825/167891895-0c96bb87-11d0-43d7-ba74-db7c6a4115ef.png)

## Penalizaciones por no asistir
1. **Inscripción automática:** Todos los equipos se inscriben automáticamente para todas las pruebas.
2. **Anuncio:** Si un equipo no puede participar en una prueba (por cualquier motivo), el líder del equipo
tiene que anunciar esto al CO al menos 60 minutos antes de que comience el turno de prueba.
3. **Penalizaciones:**
   - Un equipo que no está presente en la posición de inicio cuando su prueba programada comienza. **Penalty:** el equipo ya no puede participar en la prueba.
   - Si el equipo no anunció que no iba a participar. **Penalty:** -250pts.

## Launch y Publisher del Monologo
El launch para lanzar solo el nodo monologo con el arbol de TextToSpeech.
```
roslaunch robocup_home_education_los_ultramarinos Main.launch
```

Los publicadores de cada estado.
```
rostopic pub /msg_receive std_msgs/String "Start"
rostopic pub /msg_receive std_msgs/String "Left"
rostopic pub /msg_receive std_msgs/String "Not_vision"
rostopic pub /msg_receive std_msgs/String "Stop"
```

Cambio en el /catkin_ws/src/dialog/dialogflow_ros/dialogflow_ros/scripts/dialogflow_ros/dialogflow_client.py
```py
# line 275: rospy.loginfo(output.print_result(response.query_result))
# line 324: rospy.loginfo(output.print_result(final_result))
```

## Publicar puntos en el navegation

```py
rostopic pub /move_base_simple/goal geometry_msgs/PoseStamped '{ header: {stamp: now, frame_id: "map"}, pose: { position: {x: 0, y: 0, z: 0.0}, orientation: {w: 1.0}}}'
```
