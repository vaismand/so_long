<h1>So_Long</h1>
<p><strong>So_Long</strong> is a simple 2D game developed as a project for the 42 curriculum. Utilizing the MiniLibX library, it showcases basic game mechanics, window management, and simple graphics. Navigate through various levels, collect items, and find the exit to win.</p>

<h2>Features</h2>
<ul>
  <li>2D gameplay with intuitive controls. Players can use both "WASD" and arrow keys for navigation.</li>
  <li>Customizable maps via <code>.ber</code> files.</li>
  <li>Real-time movement tracking.</li>
  <li>Map validation using the DFS (Depth-First Search) algorithm, ensuring all maps are navigable and meet game requirements.</li>
</ul>

<h2>Getting Started</h2>
<h3>Prerequisites</h3>
<p>Ensure you have a Unix-like system with GCC, Make, and MiniLibX installed.</p>
<ul>
    <li><code>sudo apt update</code></li>
    <li><code>sudo apt install libx11-dev</code></li>
    <li><code>sudo apt install libxext-dev</code></li>
</ul>

<h3>Installation and Running</h3>
<ol>
  <li><strong>Clone the repository:</strong><br>
  <code>git clone https://github.com/vaismand/so_long</code></li>
  <li><strong>Compile the game:</strong><br>
  <code>cd so_long &amp;&amp; make</code></li>
  <li><strong>Run the game:</strong><br>
  <code>./so_long res/map/map.ber</code></li>
</ol>

<h3>Bonus Features</h3>
<ul>
  <li>Enemy patrols and sprite animations for enhanced gameplay.</li>
  <li>Movement count displayed directly in the game window.</li>
</ul>

<p>Enjoy navigating through the challenges of <strong>So_Long</strong>!</p>