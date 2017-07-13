<h2 class="block-title"><?php print $data['title']; ?></h2>
<div class="owl-carousel owl-theme" id="related-slider">
  <?php foreach ($cars as $car): ?>
    <div class="item">
      <?php print $car['node']; ?>
    </div>
  <?php endforeach ?>
</div>
