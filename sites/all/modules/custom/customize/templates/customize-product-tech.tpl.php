<h3><span>Použité technologie</span></h3>
<div class="panel-group" id="tech" role="tablist" aria-multiselectable="true">
<?php foreach ($data['tech'] as $tech): ?>
  <div class="panel">
    <div class="panel-heading" role="tab" id="heading<?php print $tech['nid']; ?>">
      <h4 class="panel-title">
        <a role="button" data-toggle="collapse" data-parent="#tech" href="#collapse<?php print $tech['nid']; ?>" aria-expanded="true" aria-controls="collapse<?php print $tech['nid']; ?>">
          <?php print $tech['title']; ?>
          <span class="glyphicon glyphicon-menu-down" aria-hidden="true"></span>
        </a>
      </h4>
    </div>
    <div id="collapse<?php print $tech['nid']; ?>" class="panel-collapse collapse" role="tabpanel" aria-labelledby="heading<?php print $tech['nid']; ?>">
      <div class="panel-body">
        <?php print $tech['body']; ?>
      </div>
    </div>
  </div>
<?php endforeach; ?>
</div>
