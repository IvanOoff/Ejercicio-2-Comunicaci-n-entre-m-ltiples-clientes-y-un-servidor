<h1 align = "center"> EXPLICACIÓN BREVE DEL FUNCIONAMIENTO </h1>
→ Este ejercicio se basa en un sistema de comunicacíon entre cliente-servidor en el que hay varios clientes que se conectan a un solo servidor através de sockets. El servidor podrá atender a varios clientes a la vez mediante un sistema de hilos, permitiendo asi una comunicación bidireccional.

<h1 align = "center"> INSTRUCCIONES DE COMPILACIÓN Y EJECUCIÓN. </h1>
→ SERVIDOR
1. Se crea el socket que permitirá la comunicación.
2. Através de un bind, asocia el socket al puerto número 5000.
3. Verifica y espera las conexiones de los clientes a través de la función listen. 
4. Acepta a los usuarios con la función accept.
5. Cre
