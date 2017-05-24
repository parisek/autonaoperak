<h2>Nejčastější dotazy</h2>
<div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">
  <?php foreach ($question as $q): ?>
    <div class="panel panel-default">
      <div class="panel-heading" role="tab" id="heading<?php print $q['id']; ?>">
        <h4 class="panel-title">
          <a role="button" data-toggle="collapse" data-parent="#accordion" href="#collapse<?php print $q['id']; ?>" aria-expanded="true" aria-controls="collapse<?php print $q['id']; ?>">
            <?php print $q['title']; ?>
          </a>
        </h4>
      </div>
      <div id="collapse<?php print $q['id']; ?>" class="panel-collapse collapse" role="tabpanel" aria-labelledby="heading<?php print $q['id']; ?>">
        <div class="panel-body">
          <?php print $q['description']; ?>
        </div>
      </div>
    </div>
  <?php endforeach; ?>
</div>
